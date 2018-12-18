/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:07:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/14 18:27:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_on_player(t_vm *vm, t_ixy xy, t_xy player_xy)
{
	return (!ft_is_on_close(vm, xy, NULL) &&
			player_xy.x < xy.x &&
			player_xy.x + vm->visu.center.player_w > xy.x &&
			player_xy.y < xy.y &&
			player_xy.y + vm->visu.center.player_h  > xy.y);
}

void	ft_fill_drag_container(t_drag_container *dc, t_ixy xy)
{
	if (dc != NULL)
	{
		dc->x = xy.x;
		dc->y = xy.y;
	}
}

void	ft_populate_drag_container(t_drag_container *dc, t_player *player,
			t_slot *slot, t_player_source source)
{
	if (dc != NULL)
	{
		dc->source = source;
		dc->player = player;
		dc->diff_x = dc->x - slot->player.x;
		dc->diff_y = dc->y - slot->player.y;
		slot->close.visible = 0;
		dc->close = &(slot->close);
	}
}

int		ft_is_on_draggable(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	int i;

	i = 0;
	ft_fill_drag_container(dc, xy);
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant && ft_is_on_player(vm, xy,
				vm->visu.positions.arena_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->player[i]),
				&(vm->visu.positions.arena_slots[i]), ARENA);
			return (1);
		}
		if (vm->local_player[i].relevant && ft_is_on_player(vm, xy,
				vm->visu.positions.local_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->local_player[i]),
				&(vm->visu.positions.local_slots[i]), LOCAL);
			return (1);
		}
		i++;
	}
	if (vm->client.upload_player.relevant && ft_is_on_player(vm, xy,
				vm->visu.positions.upload_slot.player))
	{
		ft_populate_drag_container(dc, &(vm->client.upload_player),
			&(vm->visu.positions.upload_slot), UPLOAD);
		return (1);
	}
	return (0);
}
