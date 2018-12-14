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

int			ft_is_on_player_close(t_vm *vm, t_player player, t_xy pos, t_xy close)
{
	return (player.relevant &&
			close.x + CROSS_IB < pos.x &&
			close.x + vm->visu.center.cross_border > pos.x &&
			close.y < pos.y &&
			close.y + vm->visu.center.cross_border - CROSS_IB > pos.y);
}

int			ft_is_on_arena_close(t_vm *vm, int x, int y, t_player **player)
{
	int i;
	t_xy pos;

	pos.x = x;
	pos.y = y;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_is_on_player_close(vm, vm->player[i], pos,
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
	t_xy pos;

	pos.x = x;
	pos.y = y;
	if (ft_is_on_arena_close(vm, x, y, player))
		return (1);
	else if (ft_is_on_player_close(vm, vm->client.upload_player, pos,
				vm->visu.positions.upload_slot.close))
	{
		if (player != NULL)
			*player = &(vm->client.upload_player);
		return (1);
	}
	return (0);
}
