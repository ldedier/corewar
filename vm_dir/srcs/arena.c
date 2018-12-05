/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/05 18:29:36 by ldedier          ###   ########.fr       */
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
	vm->client.active = 0;
	vm->client.port = 0;
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
*/

void		dispatch_players(t_vm *vm)
{
	int		nb;
	int		i;
	int		start;
	char	*algo;

	nb = 0;
	while (nb < vm->nb_players)
	{
		start = (MEM_SIZE / vm->nb_players) * nb;
		algo = vm->player[nb].algo;
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
