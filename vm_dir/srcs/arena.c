/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/15 22:14:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** update the number of players currently in the arena
*/

void	update_nb_players(t_vm *vm)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			res++;
		i++;
	}
	vm->nb_players = res;
}

/*
**init_vm function initializes our corewar VM's environment by setting all
**its parameters to their default value.
*/

void					init_vm(t_vm *vm, char **argv, char **env)
{
	int i;
	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = 0;
	vm->checks = MAX_CHECKS;
	vm->live.nb = 0;
	vm->live.total_pl = 0;
	vm->proc = NULL;
	vm->client.active = 0;
	vm->client.port = 0;
	vm->visu.active = 0;
	vm->cycle = 0;
	ft_bzero(vm->color, MAX_PL_COLOR);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_strlcat(vm->color, init_color_ref(env), MAX_PL_COLOR);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		i++;
	}
}

t_list	*add_process(t_vm *vm, int index, int start) //need name?
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	process->player = &vm->player[index];
	process->pc = start;
	process->reg[0] = process->player->num;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}

int		init_processes(t_vm *vm)
{
	int i;
	int	index;
	int start;

	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant && ++index && !add_process(vm, i, start))
			return (0);
	}
	vm->live.last_pl = (t_process *)(vm->proc->content);
	return (1);
}

/*
**dispatch_players function sends each player to their respective starting
**point in the arena and initializes processes for each player.
*/

void		dispatch_players(t_vm *vm)
{
	int			index;
	int			i;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	ft_lstdel_value(&vm->proc);
	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			set_color(&vm->player[i], vm->color);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
}
