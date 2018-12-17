/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:07:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/17 15:40:12 by ldedier          ###   ########.fr       */
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

void	ft_populate_drag_container_player(t_drag_container *dc, t_player *player,
			t_slot *slot, t_player_source source)
{
	if (dc != NULL)
	{
		dc->drag_enum = DRAG_PLAYER;
		dc->drag_union.drag_player.source = source;
		dc->drag_union.drag_player.player = player;
		dc->drag_union.drag_player.close = &(slot->close);
		slot->close.visible = 0;
		dc->diff_x = dc->x - slot->player.x;
		dc->diff_y = dc->y - slot->player.y;
	}
}

void	ft_populate_drag_container_vscrollbar(t_drag_container *dc,
			t_vscrollbar *vscrollbar)
{
	t_ixy xy;

	if (dc != NULL)
	{
		dc->drag_enum = DRAG_VSCROLLBAR;
		dc->drag_union.vscrollbar = vscrollbar;
		xy = ft_get_vscrollbar_bar_height_y(*vscrollbar);
		dc->diff_y = dc->y - xy.y;
	}
}

int		ft_is_on_scrollbar(t_ixy xy, t_vscrollbar  vscrollbar)
{
	t_ixy scrollbar_bar_height_y;

	if (!ft_to_print_scrollbar(vscrollbar))
		return (0);
	scrollbar_bar_height_y = ft_get_vscrollbar_bar_height_y(vscrollbar);
	return (xy.x > vscrollbar.pos.x &&
			xy.x < vscrollbar.pos.x + vscrollbar.bar_width &&
			xy.y > scrollbar_bar_height_y.y &&
			xy.y < scrollbar_bar_height_y.y + scrollbar_bar_height_y.x
			);
}

int		ft_is_on_scrollbars(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	int i;
	(void) dc;
	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_is_on_scrollbar(xy, vm->visu.players_list[i].vscrollbar))
		{
			ft_populate_drag_container_vscrollbar(dc, 
				&vm->visu.players_list[i].vscrollbar);
			return (1);
		}
		i++;
	}
	return (0);
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
			ft_populate_drag_container_player(dc, &(vm->player[i]),
				&(vm->visu.positions.arena_slots[i]), ARENA);
			return (1);
		}
		if (vm->local_player[i].relevant && ft_is_on_player(vm, xy,
				vm->visu.positions.local_slots[i].player))
		{
			ft_populate_drag_container_player(dc, &(vm->local_player[i]),
				&(vm->visu.positions.local_slots[i]), LOCAL);
			return (1);
		}
		i++;
	}
	if (vm->client.upload_player.relevant && ft_is_on_player(vm, xy,
				vm->visu.positions.upload_slot.player))
	{
		ft_populate_drag_container_player(dc, &(vm->client.upload_player),
			&(vm->visu.positions.upload_slot), UPLOAD);
		return (1);
	}
	return ft_is_on_scrollbars(vm, xy, dc);
}
