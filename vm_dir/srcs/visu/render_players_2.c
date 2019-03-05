/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:11:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:53:58 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_inner_player(t_vm *vm, SDL_Rect player_rect, t_player *player,
		t_player_source source)
{
	SDL_Rect	inner_rect;

	inner_rect.w = player_rect.w - vm->visu.center.player_inner_border * 2;
	inner_rect.h = player_rect.h - vm->visu.center.player_inner_border * 2;
	inner_rect.x = player_rect.x + vm->visu.center.player_inner_border;
	inner_rect.y = player_rect.y + vm->visu.center.player_inner_border;
	if (source / NB_SOURCES)
		SDL_FillRect(vm->visu.sdl.w_surface, &inner_rect,
			ft_get_player_color_no_drag(vm, player, PLAYER_COL, 1.2));
	else
		ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &inner_rect,
			ft_get_player_color_no_drag(vm, player, PLAYER_COL, 1.2),
			vm->visu.players_list[source].vscrollbar);
	if (source % NB_SOURCES == ARENA)
	{
		ft_render_inner_name(vm, inner_rect, player, source);
		if (ft_render_inner_number(vm, inner_rect, player, source))
			return (1);
	}
	else
		ft_render_inner_name_full(vm, player_rect, player, source);
	return (0);
}

int		ft_render_relevant_player(t_vm *vm, t_player *player,
			t_xy xy, t_player_source source)
{
	SDL_Rect rect;

	rect.x = xy.x;
	rect.y = xy.y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	if (source / NB_SOURCES)
		SDL_FillRect(vm->visu.sdl.w_surface, &rect, PLAYER_COL_BORDER);
	else
		ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &rect, PLAYER_COL_BORDER,
			vm->visu.players_list[source].vscrollbar);
	if (ft_render_inner_player(vm, rect, player, source))
		return (1);
	return (0);
}

int		ft_render_no_local_player(t_vm *vm, t_player *player, t_xy xy,
			t_player_source source)
{
	SDL_Rect rect;

	rect.x = xy.x;
	rect.y = xy.y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	if (source == ARENA)
		ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &rect,
				ft_get_player_color(vm, player, PLAYER_BACKGROUND_COL, 1.3),
				vm->visu.players_list[source].vscrollbar);
	else if (source == UPLOAD)
	{
		ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &rect,
				ft_get_player_color(vm, player, UPLOAD_COLOR, 1.3),
				vm->visu.players_list[source].vscrollbar);
	}
	return (0);
}

int		ft_render_player(t_vm *vm, t_player *pl, t_xy xy,
		t_player_source source)
{
	if (pl->relevant
		&& (source == DOWNLOADS
			|| source == LOCAL || source == SERVER
			|| (vm->visu.drag_container.drag_enum != DRAG_PLAYER
			|| vm->visu.drag_container.drag_union.drag_player.player != pl)))
	{
		if (ft_render_relevant_player(vm, pl, xy, source))
			return (1);
	}
	else if (source != LOCAL)
		return (ft_render_no_local_player(vm, pl, xy, source));
	return (0);
}

int		ft_render_dragged_player(t_vm *vm)
{
	t_xy xy;

	if (vm->visu.drag_container.drag_enum == DRAG_PLAYER &&
		vm->visu.drag_container.drag_union.drag_player.player != NULL)
	{
		xy.x = ft_fclamp(0,
			vm->visu.drag_container.x - vm->visu.drag_container.diff_x,
				vm->visu.dim.width - vm->visu.center.player_w);
		xy.y = ft_fclamp(0, vm->visu.drag_container.y
				- vm->visu.drag_container.diff_y,
				vm->visu.dim.height - vm->visu.center.player_h);
		ft_render_relevant_player(vm,
				vm->visu.drag_container.drag_union.drag_player.player, xy,
			vm->visu.drag_container.drag_union.drag_player.source + NB_SOURCES);
		if (vm->visu.drag_container.drag_union.drag_player.source == ARENA
			|| vm->visu.drag_container.drag_union.drag_player.source == UPLOAD)
			ft_render_closing_cross(vm, xy);
	}
	return (0);
}
