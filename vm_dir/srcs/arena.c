/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/28 20:08:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** update_nb_players updates the number of players currently in the arena
*/

void			update_nb_players(t_vm *vm)
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

int				ft_get_potential_num(int player_num)
{
//	ft_printf("player num = %d\n", player_num);
	if (player_num == INT_MAX) // ne se fait pas naturellement en castant?
		return (INT_MIN);
	else
		return (player_num - 1); //ancienemment return player_um + 1
	return (0);
}

/*
** ft_set_numbers function assigns each player a different number.
*/

void			ft_set_numbers(t_player *players, t_player *player)
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
//		ft_printf("after player num = %d\n", player->num);

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

void			update_buttons(t_vm *vm)
{
	if (vm->nb_players)
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 1;
	else
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 0;
}
