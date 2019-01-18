/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:07:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 21:55:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_fill_drag_container(t_drag_container *dc, t_ixy xy)
{
	if (dc != NULL)
	{
		dc->x = xy.x;
		dc->y = xy.y;
	}
}

int		ft_is_on_player_scrollbar(t_vm *vm, t_ixy xy, t_xy player_xy,
		t_vscrollbar vscrollbar)
{
	int scrolled_height;

	if (!vscrollbar.relevant)
		return (!ft_is_on_close(vm, xy, NULL) &&
				player_xy.x < xy.x &&
				player_xy.x + vm->visu.center.player_w > xy.x &&
				player_xy.y < xy.y &&
				player_xy.y + vm->visu.center.player_h > xy.y);
	else if (xy.y > vscrollbar.pos.y &&
			xy.y < vscrollbar.pos.y + vscrollbar.height)
	{
		scrolled_height = ft_get_scrolled_height(vscrollbar);
		player_xy.y -= scrolled_height;
		return ((!ft_is_on_close(vm, xy, NULL) &&
					player_xy.x < xy.x &&
					player_xy.x + vm->visu.center.player_w > xy.x &&
					player_xy.y < xy.y &&
					player_xy.y + vm->visu.center.player_h > xy.y));
	}
	return (0);
}

int		ft_is_on_draggable_locals(t_vm *vm, t_ixy xy,
		int i, t_drag_container *dc)
{
	if (vm->player[i].relevant && ft_is_on_player_scrollbar(vm, xy,
				vm->visu.positions.arena_slots[i].player,
				vm->visu.players_list[ARENA].vscrollbar))
	{
		ft_populate_drag_container_player_slot(dc, &(vm->player[i]),
				&(vm->visu.positions.arena_slots[i]), ARENA);
		return (1);
	}
	if (vm->visu.local_type == LOCAL_LOCAL &&
			vm->local_player[i].relevant && ft_is_on_player_scrollbar(vm, xy,
				vm->visu.positions.local_slots[i].player,
				vm->visu.players_list[LOCAL].vscrollbar))
	{
		ft_populate_drag_container_player_slot(dc, &(vm->local_player[i]),
				&(vm->visu.positions.local_slots[i]), LOCAL);
		return (1);
	}
	return (0);
}

int		ft_is_on_draggable(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	int i;

	if (vm->visu.phase == PHASE_INIT && vm->visu.notification.image_index == -1)
	{
		i = 0;
		ft_fill_drag_container(dc, xy);
		while (i < MAX_PLAYERS)
		{
			if (ft_is_on_draggable_locals(vm, xy, i, dc))
				return (1);
			i++;
		}
		if (vm->client.active && ft_is_on_client_players(vm, xy, dc))
			return (1);
		if (vm->visu.local_type == LOCAL_DOWNLOAD &&
				ft_is_on_download_players(vm, xy, dc))
			return (1);
	}
	return (ft_is_on_scrollbars(vm, xy, dc));
}
