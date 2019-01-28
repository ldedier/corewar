/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/28 18:35:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			clear_vm(t_vm *vm)
{
		vm->live = 0;
		vm->proc = NULL;
		vm->nb = 1;
		vm->total_cycle = 0;
		vm->cycle = 0;
		ft_bzero(vm->arena, MEM_SIZE);
		init_players(vm);
}

void			init_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = NULL;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 0;
		ft_bzero(vm->player[i].aff_buf, MAX_AFF_LEN);
	}
}

/*
** init_vm function initializes our corewar VM's environment by setting all
** its parameters to their default value.
*/

void			init_vm(t_vm *vm, char **argv, char **env)
{
	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = 0;
	vm->checks = MAX_CHECKS;
	vm->live = 0;
	vm->proc = NULL;
	vm->client.active = 0;
	vm->client.port = 0;
	vm->visu.active = 0;
	vm->nb = 1;
	vm->total_cycle = 1;
	vm->cycle = 1;
	vm->nb_players = 0;
	ft_bzero(vm->color, MAX_PL_COLOR);
	ft_strlcat(vm->color, init_color_ref(env), MAX_PL_COLOR);
	init_players(vm);
}

/*
** add_process function is used by init_processes to add a process to the list
*/

t_list			*add_process(t_vm *vm, int index, int start, t_process *src)
{
	t_process	*process;
	static int	nb = 0;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	if (src)
	{
		ft_memmove(process, src, sizeof(t_process));
		ft_bzero((void *)&process->pending_ins, sizeof(t_instruction));
		process->live = 0;
//		process->live_cycle = 0;
//		process->live_cycle = vm->total_cycle;
		++process->player->nb_proc;
	}
	else
	{
		process->player = &vm->player[index];
		process->pc = start;
		process->reg[0] = process->player->num; 
//		process->live = 0;
	}
	process->nb = ++nb;
//	ft_printf("\n\ncycle = %d new process nb = %d, last live = %d, cycle to die = %d\n\n", vm->total_cycle, process->nb, process->live_cycle, vm->c_to_die);
//	if (src)
//		ft_printf("old src live num = %d cycle = %d\n", src->nb, src->live_cycle);
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	int i = 1;
	for (t_list *tmp = vm->proc; tmp; tmp = tmp->next)
		++i;
//	ft_printf("%d process in list\n", i);
	return (vm->proc);
}

/*
** init_processes function initializes each players' starting process.
*/

int				init_processes(t_vm *vm)
{
	int i;
	int	index;
	int start;

	i = -1;
	index = 1;
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant && ++index && !add_process(vm, i, start, NULL))
			return (0);
		vm->player[i].nb_proc = 1;
		vm->winner = ((t_process *)(vm->proc->content))->player;
	}
	return (1);
}

/*
** dispatch_players_init and dispatch_players functions send each player
** to their respective starting point in the arena.
*/

void			dispatch_players_init(t_vm *vm)
{
	int			index;
	int			i;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	i = -1;
	index = 0;
	if (!vm->visu.active)
		ft_printf("Introducing contestants...");
	while (++i < MAX_PLAYERS)
	{
		set_color(&vm->player[i], vm->color);
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			if (!vm->visu.active)
				display_player_intro(&vm->player[i]);
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
	}
}

void			dispatch_players(t_vm *vm, t_player *player)
{
	int			index;
	int			i;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
	{
		if (set_color(&vm->player[i], vm->color) && player != &vm->player[i])
			ft_set_numbers(vm->player, &(vm->player[i]));
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			display_player_intro(&vm->player[i]);
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
	}
	update_buttons(vm);
}
