/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_draggable_server.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 19:43:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/09 20:34:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_is_on_player_scrollbar_nocross(t_vm *vm, t_ixy xy,
				t_xy player_xy, t_vscrollbar vscrollbar)
{
	int scrolled_height;

	if (!vscrollbar.relevant)
		return ((player_xy.x < xy.x
			&& player_xy.x + vm->visu.center.player_w > xy.x
			&& player_xy.y < xy.y
			&& player_xy.y + vm->visu.center.player_h > xy.y));
	else if (xy.y > vscrollbar.pos.y
			&& xy.y < vscrollbar.pos.y + vscrollbar.height)
	{
		scrolled_height = ft_get_scrolled_height(vscrollbar);
		player_xy.y -= scrolled_height;
		return (player_xy.x < xy.x
			&& player_xy.x + vm->visu.center.player_w > xy.x
			&& player_xy.y < xy.y
			&& player_xy.y + vm->visu.center.player_h > xy.y);
	}
	return (0);
}

static int	ft_is_on_upload_slot(t_vm *vm, t_ixy xy, t_drag_container *dc)
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

static int	ft_is_on_server_slots(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	t_list		*ptr;
	t_xy		p_pos;
	t_center	c;

	c = vm->visu.center;
	ptr = vm->client.client_slots;
	p_pos.x = vm->visu.center.dashboard_x + vm->visu.center.labscore_left
		+ vm->visu.center.labscore_width + vm->visu.center.labscore_right
		+ vm->visu.center.score_width + vm->visu.center.score_right;
	p_pos.y = vm->visu.players_list[SERVER].vscrollbar.pos.y + c.player_top;
	while (ptr != NULL)
	{
		if (ft_is_on_player_scrollbar_nocross(vm, xy, p_pos,
				vm->visu.players_list[SERVER].vscrollbar))
		{
			ft_populate_drag_container_player_client_slot(dc, ptr->content,
					p_pos, ft_get_scrolled_height(vm->visu.
							players_list[SERVER].vscrollbar));
			return (1);
		}
		p_pos.y += vm->visu.center.player_padding + vm->visu.center.player_h;
		ptr = ptr->next;
	}
	return (0);
}

int			ft_is_on_download_players(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	t_list		*ptr;
	t_xy		player_pos;
	t_center	c;

	c = vm->visu.center;
	ptr = vm->visu.downloaded_players;
	player_pos.x = c.dashboard_mid_x + c.player_left - (ft_to_print_scrollbar(
		vm->visu.players_list[DOWNLOADS].vscrollbar) ? c.scrollbar_width
		/ 2 : 0);
	player_pos.y = vm->visu.players_list[DOWNLOADS].vscrollbar.pos.y
		+ c.player_top;
	while (ptr != NULL)
	{
		if (ft_is_on_player_scrollbar_nocross(vm, xy, player_pos,
				vm->visu.players_list[DOWNLOADS].vscrollbar))
		{
			ft_populate_drag_container_player_download(dc, ptr->content,
				player_pos, ft_get_scrolled_height(vm->visu.
						players_list[DOWNLOADS].vscrollbar));
			return (1);
		}
		player_pos.y += c.player_padding + c.player_h;
		ptr = ptr->next;
	}
	return (0);
}

int			ft_is_on_client_players(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	if (ft_is_on_upload_slot(vm, xy, dc))
		return (1);
	else if (ft_is_on_server_slots(vm, xy, dc))
		return (1);
	return (0);
}
