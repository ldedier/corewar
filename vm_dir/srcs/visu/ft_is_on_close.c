/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_on_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:04:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 19:04:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_is_on_player_close(t_player player, int x, int y, t_xy close)
{
	return (player.relevant &&
			close.x + CROSS_IB < x &&
			close.x + CROSS_BORDER > x &&
			close.y < y &&
			close.y + CROSS_BORDER - CROSS_IB > y);
}

int			ft_is_on_arena_close(t_vm *vm, int x, int y, t_player **player)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_is_on_player_close(vm->player[i], x, y,
				vm->visu.positions.arena_slots[i].close))
		{
			if (player != NULL)
				*player = &(vm->player[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_is_on_close(t_vm *vm, int x, int y, t_player **player)
{
	if (ft_is_on_arena_close(vm, x, y, player))
		return (1);
	else if (ft_is_on_player_close(vm->client.upload_player, x, y,
				vm->visu.positions.upload_slot.close))
	{
		if (player != NULL)
			*player = &(vm->client.upload_player);
		return (1);
	}
	return (0);
}
