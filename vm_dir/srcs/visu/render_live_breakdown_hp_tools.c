/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown_hp_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 22:26:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 22:37:39 by ldedier          ###   ########.fr       */
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
		return ((double)lives_player_1 /
			(double)(lives_player_1 + lives_player_2));
}

int		ft_moy(int val1, int val2)
{
	return ((val1 + val2) / 2);
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
