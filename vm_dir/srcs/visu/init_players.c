/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:12:22 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/25 14:21:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "vm.h"

static int			ft_get_potential_num(int player_num)
{
		return (player_num == INT_MAX ? INT_MIN : player_num - 1);
}

/*
** ft_set_numbers function assigns each player a different number.
*/

static void			ft_set_numbers(t_player *players, t_player *player)
{
	int i;
	int j;
	int found;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].relevant && player != &players[i])
		{
			player->num = ft_get_potential_num(players[i].num);
			found = 1;
			j = -1;
			while (++j < MAX_PLAYERS)
			{
				if (i != j && players[j].relevant && &players[j] != player &&
						player->num == players[j].num)
				{
					found = 0;
					break ;
				}
			}
			if (found)
				return ;
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
