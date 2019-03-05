/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown_hp_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 22:26:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:23:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** return the player1 / player2 live ratio
*/

double	get_magic_ratio(t_vm *vm, int lives_player_1, int lives_player_2)
{
	int		i;
	int		nb;

	nb = 0;
	if (vm->proc == NULL)
	{
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (vm->player[i].relevant)
			{
				if (vm->winner == &vm->player[i])
					return (nb == 0 ? 1.30 : -0.30);
				nb++;
			}
			i++;
		}
		return (0.5);
	}
	else if (!lives_player_1 && !lives_player_2)
		return (0.5);
	else
		return (ft_fclamp(0.05,
			(double)lives_player_1 / (double)(lives_player_1 + lives_player_2),
			0.98));
}

double	ft_fmoy(double val1, double val2)
{
	return ((val1 + val2) / 2.0);
}

double	ft_flerp(double val1, double val2, double t)
{
	return ((t * val2) + (1 - t) * (val1));
}

void	populate_hp_player_title_rect(t_vm *vm, SDL_Rect *rect)
{
	rect->x = vm->visu.center.dashboard_x
		+ vm->visu.center.live_breakdown_hp_players_side;
	rect->y = vm->visu.center.live_breakdown_hp_y
		+ vm->visu.center.live_breakdown_hp_title_top
		+ vm->visu.center.live_breakdown_title_h
		+ vm->visu.center.live_breakdown_hp_title_bottom;
	rect->w = vm->visu.center.entry_max_w;
	rect->h = vm->visu.center.live_breakdown_hp_players_h;
}

void	ft_get_player_lives(t_vm *vm, int *nb_live_player_1,
		int *nb_live_player_2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
		{
			if (!j)
				*nb_live_player_1 = vm->player[i].live;
			else
			{
				*nb_live_player_2 = vm->player[i].live;
				return ;
			}
			j++;
		}
		i++;
	}
}
