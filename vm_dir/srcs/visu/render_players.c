/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:47:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/18 17:19:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_copy_str_to_surface(t_vm *vm, char *str,
			SDL_Rect rect, t_ixy col_source)
{
	int			i;
	SDL_Rect	char_rect;
	int			len;

	char_rect.h = rect.h;
	char_rect.y = rect.y;
	char_rect.x = rect.x;
	len = ft_strlen(str);
	char_rect.w = rect.w / len;
	i = 0;
	while (str[i])
	{
		if (ft_blit_scaled_scrollbar(&vm->visu.sdl,
			vm->visu.sdl.atlas[col_source.x][(int)str[i]].surface,
			char_rect,
			vm->visu.players_list[col_source.y].vscrollbar) < 0)
			return (ft_net_error());
		char_rect.x += char_rect.w;
		i++;
	}
	return (0);
}

int		ft_render_closing_cross(t_vm *vm, t_xy xy)
{
	SDL_Rect	cross_rect;

	cross_rect.w = vm->visu.center.cross_border;
	cross_rect.h = vm->visu.center.cross_border;
	cross_rect.x = xy.x + vm->visu.center.player_w - vm->visu.center.cross_border;
	cross_rect.y = xy.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[CLOSE], NULL,
			vm->visu.sdl.w_surface, &cross_rect) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_get_player_color_no_drag(t_vm *vm, t_player *player,
			int initial_color, float value)
{
	t_color_manager c;

	if (player != vm->visu.drop_container.player ||
			player == vm->visu.drag_container.drag_union.drag_player.player ||
				vm->visu.drag_container.drag_enum != DRAG_PLAYER)
		return (initial_color);
	else
	{
		c = ft_get_color(initial_color);
		return (ft_scale_color(c, value).color);
	}
}


int		ft_get_player_color(t_vm *vm, t_player *player, int initial_color,
			float value)
{
	t_color_manager c;

	if (player != vm->visu.drop_container.player ||
		vm->visu.drag_container.drag_enum != DRAG_PLAYER)
		return (initial_color);
	else
	{
		c = ft_get_color(initial_color);
		return (ft_scale_color(c, value).color);
	}
}

void	ft_render_player_name(t_vm *vm, SDL_Rect player_rect, t_player *player,
		t_player_source source)
{
	SDL_Rect	name_rect;
	SDL_Rect	inner_rect;
	t_ixy		col_source;

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
	name_rect.w = player_rect.w / 2;
	name_rect.h = player_rect.h / 2;
	name_rect.x = player_rect.x + player_rect.w / 4;
	name_rect.y = player_rect.y + player_rect.h / 4;
	col_source.y = source;
	if (source % NB_SOURCES == ARENA)
		col_source.x = player->color.index;
	else
		col_source.x = MAX_PL_COLOR;
	ft_copy_str_to_surface(vm, player->name, name_rect, col_source);

}

void	ft_render_relevant_player(t_vm *vm, t_player *player,
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
	ft_render_player_name(vm, rect, player, source);
}

int		ft_render_player(t_vm *vm, t_player *player, t_xy xy,
			t_player_source source)
{
	SDL_Rect rect;

	if (player->relevant && (source == LOCAL || source == SERVER ||
		 vm->visu.drag_container.drag_union.drag_player.player != player)) //WATCH FOR ENUM MAYBE
		ft_render_relevant_player(vm, player, xy, source);
	else if (source != LOCAL)
	{
		rect.x = xy.x;
		rect.y = xy.y;
		rect.w = vm->visu.center.player_w;
		rect.h = vm->visu.center.player_h;
		if (source == ARENA)
			ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &rect,
					ft_get_player_color(vm, player,PLAYER_BACKGROUND_COL, 1.3),
					vm->visu.players_list[source].vscrollbar);
		else if (source == UPLOAD)
		{
			ft_fill_rect_scrollbar(vm->visu.sdl.w_surface, &rect,
					ft_get_player_color(vm, player, UPLOAD_COLOR, 1.3),
					vm->visu.players_list[source].vscrollbar);
			rect.x += rect.w / 6;
			rect.y += rect.h / 6;
			rect.w -= rect.w / 3;
			rect.h -= rect.h / 3;
			if (ft_blit_scaled_scrollbar(&vm->visu.sdl, vm->visu.sdl.titles[UPLOAD_HERE],
				rect,
				vm->visu.players_list[source].vscrollbar) < 0)
				return (ft_net_error());
		}
	}
	return (0);
}

int		ft_render_title(t_vm *vm, int title_index, double x, double y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_mid_width -
		2 * vm->visu.center.title_side;
	rect.h = vm->visu.center.title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[title_index],
			NULL, vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
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
		xy.y = ft_fclamp(0, vm->visu.drag_container.y -
				vm->visu.drag_container.diff_y,
					vm->visu.dim.height - vm->visu.center.player_h);
		ft_render_relevant_player(vm,
				vm->visu.drag_container.drag_union.drag_player.player, xy,
			vm->visu.drag_container.drag_union.drag_player.source + NB_SOURCES);
		if (vm->visu.drag_container.drag_union.drag_player.source == ARENA ||
				vm->visu.drag_container.drag_union.drag_player.source == UPLOAD)
			ft_render_closing_cross(vm, xy);
	}
	return (0);
}

int		ft_render_arena_players(t_vm *vm)
{
	int i;

	ft_render_title(vm, ARENA, vm->visu.center.dashboard_x +
			vm->visu.center.title_side, vm->visu.center.title_top);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, &(vm->player[i]),
			vm->visu.positions.arena_slots[i].player, ARENA);
		i++;
	}
	return (0);
}

int		ft_render_local_players(t_vm *vm)
{
	int i;

	ft_render_title(vm, LOCAL, vm->visu.center.dashboard_mid_x +
			vm->visu.center.title_side, vm->visu.center.title_top);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, &(vm->local_player[i]),
			vm->visu.positions.local_slots[i].player, LOCAL);
		i++;
	}
	return (0);
}

int		ft_render_players(t_vm *vm)
{
	ft_render_arena_players(vm);
	ft_render_local_players(vm);
	return (0);
}
