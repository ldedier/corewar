/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_drag_container.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:12:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 21:55:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_populate_drag_container_player(t_drag_container *dc,
			t_player *player, t_player_source source)
{
	if (dc != NULL)
	{
		dc->drag_enum = DRAG_PLAYER;
		dc->drag_union.drag_player.source = source;
		dc->drag_union.drag_player.player = player;
	}
}

void	ft_populate_drag_container_player_slot(t_drag_container *dc,
			t_player *player, t_slot *slot, t_player_source source)
{
	if (dc != NULL)
	{
		ft_populate_drag_container_player(dc, player, source);
		dc->drag_union.drag_player.close = &(slot->close);
		slot->close.visible = 0;
		dc->diff_x = dc->x - slot->player.x;
		if (ft_to_print_scrollbar(dc->parent->players_list[source].vscrollbar))
			dc->diff_y = dc->y - slot->player.y +
				ft_get_scrolled_height(dc->parent->players_list[source].
					vscrollbar);
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
		dc->drag_union.drag_player.client_slot = client_slot;
	}
}

void	ft_populate_drag_container_player_download(t_drag_container *dc,
			t_player *player, t_xy player_pos, int scrolled_h)
{
	if (dc != NULL)
	{
		ft_populate_drag_container_player(dc, player, DOWNLOADS);
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
