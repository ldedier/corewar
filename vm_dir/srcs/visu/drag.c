/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:07:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/18 21:42:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

int		ft_is_on_server_player(t_vm *vm, t_ixy xy, t_xy player_xy,
			t_vscrollbar vscrollbar)
{
	int scrolled_height;

	if (!vscrollbar.relevant)
		return ((player_xy.x < xy.x &&
			player_xy.x + vm->visu.center.player_w > xy.x &&
			player_xy.y < xy.y &&
			player_xy.y + vm->visu.center.player_h  > xy.y));
	else if (xy.y > vscrollbar.pos.y &&
			xy.y < vscrollbar.pos.y + vscrollbar.height)
	{
		scrolled_height = ft_get_scrolled_height(vscrollbar);
		player_xy.y -= scrolled_height; 
		return (player_xy.x < xy.x &&
				player_xy.x + vm->visu.center.player_w > xy.x &&
				player_xy.y < xy.y &&
				player_xy.y + vm->visu.center.player_h > xy.y);
	}
	return (0);
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
		t_player_source source)
{
	if (dc != NULL)
	{
		dc->drag_enum = DRAG_PLAYER;
		dc->drag_union.drag_player.source = source;
		dc->drag_union.drag_player.player = player;
	}
}

void	ft_populate_drag_container_player_slot(t_drag_container *dc, t_player *player,
			t_slot *slot, t_player_source source)
{
	if (dc != NULL)
	{
		ft_populate_drag_container_player(dc, player, source);
		dc->drag_union.drag_player.close = &(slot->close);
		slot->close.visible = 0;
		dc->diff_x = dc->x - slot->player.x;
		if (ft_to_print_scrollbar(dc->parent->players_list[source].vscrollbar))
			dc->diff_y = dc->y - slot->player.y +
				ft_get_scrolled_height(dc->parent->players_list[source].vscrollbar);
		else
			dc->diff_y = dc->y - slot->player.y;
	}
}

void	ft_populate_drag_container_player_client_slot(t_drag_container *dc,
			t_client_slot *client_slot, t_xy player_pos, int scrolled_h)
{
	if (dc != NULL)
	{
		ft_populate_drag_container_player(dc, client_slot->player, SERVER);
		dc->diff_x = dc->x - player_pos.x;
		dc->diff_y = dc->y - player_pos.y + scrolled_h;
		dc->drag_union.drag_player.close = NULL;
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

int		ft_is_on_upload_slot(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	if (vm->client.upload_player.relevant && ft_is_on_player_scrollbar(vm, xy,
		vm->visu.positions.upload_slot.player,
			vm->visu.players_list[UPLOAD].vscrollbar))
	{
		ft_populate_drag_container_player_slot(dc, &(vm->client.upload_player),
			&(vm->visu.positions.upload_slot), UPLOAD);
		return (1);
	}
	return (0);
}

int		ft_is_on_server_slots(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	t_list	*ptr;
	t_xy	player_pos;
	double	y;
	double	x;

	y = vm->visu.players_list[SERVER].vscrollbar.pos.y;
	ptr = vm->client.client_slots;
	x = vm->visu.center.dashboard_x + vm->visu.center.labscore_left +
		vm->visu.center.labscore_width + vm->visu.center.labscore_right
		+ vm->visu.center.score_width + vm->visu.center.score_right;
	player_pos.x = x;
	y += vm->visu.center.player_top;
	while (ptr != NULL)
	{
		player_pos.y= y;
		if (ft_is_on_server_player(vm, xy, player_pos,
				vm->visu.players_list[SERVER].vscrollbar))
		{
			ft_populate_drag_container_player_client_slot(dc, ptr->content,
					player_pos,
						ft_get_scrolled_height(vm->visu.
							players_list[SERVER].vscrollbar));
			return (1);
		}
		y += vm->visu.center.player_padding + vm->visu.center.player_h;
		ptr = ptr->next;
	}
	return (0);
}

int		ft_is_on_scrollbar_bar(t_ixy xy, t_vscrollbar  vscrollbar)
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

	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_is_on_scrollbar_bar(xy, vm->visu.players_list[i].vscrollbar))
		{
			ft_populate_drag_container_vscrollbar(dc, 
				&vm->visu.players_list[i].vscrollbar);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_is_on_client_players(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	if (ft_is_on_upload_slot(vm, xy, dc))
		return (1);
	else if (ft_is_on_server_slots(vm, xy, dc))
		return (1);
	return (0);
}

int		ft_is_on_draggable(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	int i;

	i = 0;
	ft_fill_drag_container(dc, xy);
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant && ft_is_on_player_scrollbar(vm, xy,
				vm->visu.positions.arena_slots[i].player,
				vm->visu.players_list[ARENA].vscrollbar))
		{
			ft_populate_drag_container_player_slot(dc, &(vm->player[i]),
				&(vm->visu.positions.arena_slots[i]), ARENA);
			return (1);
		}
		if (vm->local_player[i].relevant && ft_is_on_player_scrollbar(vm, xy,
				vm->visu.positions.local_slots[i].player,
				vm->visu.players_list[LOCAL].vscrollbar))
		{
			ft_populate_drag_container_player_slot(dc, &(vm->local_player[i]),
				&(vm->visu.positions.local_slots[i]), LOCAL);
			return (1);
		}
		i++;
	}
	if (vm->client.active && ft_is_on_client_players(vm, xy, dc))
		return (1);
	return (ft_is_on_scrollbars(vm, xy, dc));
}
