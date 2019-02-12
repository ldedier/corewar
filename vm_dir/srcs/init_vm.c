/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/08 20:04:44 by emuckens         ###   ########.fr       */
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
		vm->c_to_die = CYCLE_TO_DIE;
		ft_bzero(vm->arena, MEM_SIZE);
		ft_bzero(vm->metarena, sizeof(vm->metarena));
//		init_players(vm);
}

/*
** init_vm function initializes our corewar VM's environment by setting all
** its parametzers to their default value.
*/

void			init_vm(t_vm *vm, char **argv, char **env)
{
	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = -1;
	vm->checks = MAX_CHECKS;
	vm->live = 0;
	vm->proc = NULL;
	vm->client.active = 0;
	vm->client.port = 0;
	vm->visu.active = 0;
	vm->nb = -1;
	vm->total_cycle = 1;
	vm->cycle = 1;
	vm->nb_players = 0;
	vm->display = 0;
	vm->issued_live = 0;
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
		process->player = src->player;
		process->ins_bytelen = src->ins_bytelen;
		process->pending_ins.op = src->pending_ins.op;
		process->live_cycle = src->live_cycle;
		ft_memmove(process->reg, src->reg, REG_NUMBER * sizeof(int));
		process->pc = src->pc;
		process->carry = src->carry;
		process->cycle = src->cycle;
		process->ins_cycle = src->ins_cycle;
		process->pending_ins.op = NULL;
		process->pending_ins.params[0].nb_bytes = 0;
		process->pending_ins.params[1].nb_bytes = 0;
		process->pending_ins.params[2].nb_bytes = 0;
		process->live = 0;
		++process->player->nb_proc;
	}
	else
	{
		process->player = &vm->player[index];
		process->pc = start;
		process->reg[0] = process->player->num;
		process->ins_bytelen = 0;
	}
	process->nb = ++nb;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
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
