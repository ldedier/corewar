/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:12:22 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 20:24:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "vm.h"

static void		update_buttons(t_vm *vm)
{
	if (vm->nb_players)
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 1;
	else
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 0;
}

/*
** ft_set_numbers function assigns each player a different number.
*/

static void		ft_set_numbers(t_player *players, t_player *player)
{
	int i;
	int found;

	player->num = -1;
	found = 0;
	while (!found)
	{
		i = -1;
		found = 1;
		while (++i < MAX_PLAYERS)
			if (players[i].relevant && player != &players[i])
				if (player->num == players[i].num)
				{
					found = 0;
					player->num--;
					break ;
				}
	}
}

static void		init_dispatch_players(t_vm *vm)
{
	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
}

static int		init_player_values(t_player *player)
{
	player->live = 0;
	player->last_live_cycle = 0;
	return (1);
}

void			dispatch_players(t_vm *vm, t_player *player)
{
	int			index;
	int			i;
	int			j;
	int			start;

	init_dispatch_players(vm);
	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
	{
		if (set_color_sdl(vm, &vm->player[i]) && player != &vm->player[i])
			ft_set_numbers(vm->player, &(vm->player[i]));
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			init_player_values(&vm->player[i]);
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
