/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:07:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 19:07:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_on_player(t_vm *vm, int x, int y, t_xy player_xy)
{
	return (!ft_is_on_close(vm, x, y, NULL) &&
			player_xy.x < x &&
			player_xy.x + vm->visu.center.player_w > x &&
			player_xy.y < y &&
			player_xy.y + vm->visu.center.player_h  > y);
}

void	ft_fill_drag_container(t_drag_container *dc, int x, int y)
{
	if (dc != NULL)
	{
		dc->x = x;
		dc->y = y;
	}
}

void	ft_populate_drag_container(t_drag_container *dc, t_player *player,
			t_xy player_xy, t_player_source source)
{
	if (dc != NULL)
	{
		dc->source = source;
		dc->player = player;
		dc->diff_x = dc->x - player_xy.x;
		dc->diff_y = dc->y - player_xy.y;
	}
}

int		ft_is_on_draggable(t_vm *vm, int x, int y, t_drag_container *dc)
{
	int i;

	i = 0;
	ft_fill_drag_container(dc, x, y);
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant && ft_is_on_player(vm, x, y,
				vm->visu.positions.arena_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->player[i]),
				vm->visu.positions.arena_slots[i].player, ARENA);
			return (1);
		}
		if (vm->local_player[i].relevant && ft_is_on_player(vm, x, y,
					vm->visu.positions.local_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->local_player[i]),
				vm->visu.positions.local_slots[i].player, LOCAL);
			return (1);
		}
		i++;
	}
	if (vm->client.upload_player.relevant && ft_is_on_player(vm, x, y,
				vm->visu.positions.upload_slot.player))
	{
		ft_populate_drag_container(dc, &(vm->client.upload_player),
				vm->visu.positions.upload_slot.player, UPLOAD);
		return (1);
	}
	return (0);
}
