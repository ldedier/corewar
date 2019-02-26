/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:20:21 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 21:43:14 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_players function initializes each player's structures' parameters to
** their default value
*/

void			init_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = 1;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 0;
		vm->player[i].num_type = -1;
		ft_bzero(vm->player[i].aff_buf, MAX_AFF_LEN);
	}
}

/*
** update_nb_players updates the number of players currently in the arena
*/

void			update_nb_players(t_vm *vm)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			res++;
	}
	vm->nb_players = res;
}

/*
** store each player data to their respective starting point in the arena
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
	ft_printf("Introducing contestants...");
	while (++i < MAX_PLAYERS)
	{
		set_color(&vm->player[i], vm->color);
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			vm->player[i].color.term[0] = 0;
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

void			init_local_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->local_player[i] = vm->player[i];
		vm->local_player[i].color.value = 1;
		vm->local_player[i].num = vm->nb;
		i++;
	}
}
