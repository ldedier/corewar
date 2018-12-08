/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/08 18:20:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**init_vm function initializes our corewar VM's environment by setting all
**its parameters to their default value.
*/

void		init_vm(t_vm *vm, char **argv)
{
	int		i;

	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = 0;
	vm->max_checks = 0;
	vm->live.nb = 0;
	vm->live.total_pl = 0;
	vm->live.last_pl = -1;
	vm->dead = 0;
	ft_strcpy(vm->color.player[1], COL_BPL1);
	ft_strcpy(vm->color.player[3], COL_BPL2);
	ft_strcpy(vm->color.player[5], COL_BPL3);
	ft_strcpy(vm->color.player[7], COL_BPL4);
	ft_strcpy(vm->color.player[0], COL_FPL1);
	ft_strcpy(vm->color.player[2], COL_FPL2);
	ft_strcpy(vm->color.player[4], COL_FPL3);
	ft_strcpy(vm->color.player[6], COL_FPL4);
//	vm->client.active = 0;
//	vm->client.port = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].hex = 0;
		i++;
	}
}

/*
**dispatch_players function sends each player to their respective starting
**point in the arena.
** Initialize processes
*/

void		dispatch_players(t_vm *vm)
{
	int		nb;
	int		i;
	int		start;
	char	*algo;

	nb = 0;
	vm->proc = (t_process *)ft_memalloc(sizeof(t_process) * vm->nb_players);
	while (nb < vm->nb_players)
	{
		start = (MEM_SIZE / vm->nb_players) * nb;
		algo = vm->player[nb].algo;
		vm->proc[nb].pc = start;
		vm->proc[nb].id = nb;
		i = 0;
		while (i < vm->player[nb].algo_len)
		{
			vm->arena[start].hex = algo[i];
			i++;
			start++;
		}
		nb++;
	}
}
