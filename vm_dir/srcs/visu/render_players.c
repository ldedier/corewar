/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:47:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/12 23:47:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_copy_str_to_surface(t_vm *vm, SDL_Surface *surface, char *str,
			SDL_Rect rect)
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
		if (SDL_BlitScaled(vm->visu.sdl.atlas[(int)str[i]].surface, NULL,
				surface, &char_rect) < 0)
			return (ft_net_error());
		char_rect.x += char_rect.w;
		i++;
	}
	return (0);
}

int		ft_render_closing_cross(t_vm *vm, t_slot slot)
{
	SDL_Rect	cross_rect;

	cross_rect.w = CROSS_BORDER;
	cross_rect.h = CROSS_BORDER;
	cross_rect.x = slot.close.x;
	cross_rect.y = slot.close.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[CLOSE], NULL,
			vm->visu.sdl.w_surface, &cross_rect) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_render_closing_cross_no_slot(t_vm *vm, t_xy xy)
{
	SDL_Rect	cross_rect;

	cross_rect.w = CROSS_BORDER;
	cross_rect.h = CROSS_BORDER;
	cross_rect.x = xy.x + vm->visu.center.player_w - CROSS_BORDER;
	cross_rect.y = xy.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[CLOSE], NULL,
			vm->visu.sdl.w_surface, &cross_rect) < 0)
		return (ft_net_error());
	return (0);
}

void	ft_render_player_name(t_vm *vm, SDL_Rect player_rect, t_player *player)
{
	SDL_Rect name_rect;
	SDL_Rect inner_rect;

	inner_rect.w = player_rect.w - PLAYER_INNER_BORDER * 2;
	inner_rect.h = player_rect.h - PLAYER_INNER_BORDER * 2;
	inner_rect.x = player_rect.x + PLAYER_INNER_BORDER;
	inner_rect.y = player_rect.y + PLAYER_INNER_BORDER;
	SDL_FillRect(vm->visu.sdl.w_surface, &inner_rect, PLAYER_COL);
	name_rect.w = player_rect.w / 2;
	name_rect.h = player_rect.h / 2;
	name_rect.x = player_rect.x + player_rect.w / 4;
	name_rect.y = player_rect.y + player_rect.h / 4;
	ft_copy_str_to_surface(vm, vm->visu.sdl.w_surface, player->name, name_rect);
}

void	ft_render_relevant_player_no_slot(t_vm *vm, t_player *player,
			t_xy xy, char cross)
{
	SDL_Rect rect;

	rect.x = xy.x;
	rect.y = xy.y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, PLAYER_COL_BORDER);
	ft_render_player_name(vm, rect, player);
	if (cross)
		ft_render_closing_cross_no_slot(vm, xy);
}

void	ft_render_relevant_player(t_vm *vm, t_player *player, t_slot slot)
{
	SDL_Rect rect;

	rect.x = slot.player.x;
	rect.y = slot.player.y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, PLAYER_COL_BORDER);
	ft_render_player_name(vm, rect, player);
	if (slot.close.x != -1)
		ft_render_closing_cross(vm, slot);
}

void	ft_render_player(t_vm *vm, t_player *player, t_slot slot,
			int title_index)
{
	SDL_Rect rect;

	if (player->relevant && (title_index == LOCAL_PLAYERS ||
			vm->visu.drag_container.player != player))
		ft_render_relevant_player(vm, player, slot);
	else if (title_index == BATTLEFIELD)
	{
		rect.x = slot.player.x;
		rect.y = slot.player.y;
		rect.w = vm->visu.center.player_w;
		rect.h = vm->visu.center.player_h;
		if (player != vm->visu.drop_container.player)
			SDL_FillRect(vm->visu.sdl.w_surface, &rect, PLAYER_BACKGROUND_COL);
		else
			SDL_FillRect(vm->visu.sdl.w_surface, &rect, PLAYER_HOVERED_BG_COL);
	}
}

void	ft_render_title(t_vm *vm, int title_index, double x, double y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_mid_width -
		2 * vm->visu.center.title_side;
	rect.h = vm->visu.center.title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[title_index], NULL,
			vm->visu.sdl.w_surface, &rect) < 0)
		ft_net_error();
}

void	ft_render_player_pool(t_vm *vm, t_player players[MAX_PLAYERS],
			t_slot slots[MAX_PLAYERS], int title_index)
{
	int		i;
	int		x_offset;

	if (title_index == BATTLEFIELD)
		x_offset = vm->visu.center.dashboard_x;
	else
		x_offset = vm->visu.center.dashboard_mid_x;
	ft_render_title(vm, title_index, x_offset + vm->visu.center.title_side,
		vm->visu.center.title_top);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, &(players[i]), slots[i], title_index);
		i++;
	}
}

int		ft_render_dragged_player(t_vm *vm)
{
	t_xy xy;
	
	if (vm->visu.drag_container.player != NULL)
	{
		xy.x = ft_fclamp(0,
			vm->visu.drag_container.x - vm->visu.drag_container.diff_x,
				vm->visu.dim.width - vm->visu.center.player_w);
		xy.y = ft_fclamp(0, vm->visu.drag_container.y -
				vm->visu.drag_container.diff_y,
					vm->visu.dim.height - vm->visu.center.player_h);
		ft_render_relevant_player_no_slot(vm, vm->visu.drag_container.player,
			xy, vm->visu.drag_container.from_arena);
	}
	return (0);
}

int		ft_render_players(t_vm *vm)
{
	ft_render_player_pool(vm, vm->player, vm->visu.positions.arena_slots,
				BATTLEFIELD);
	ft_render_player_pool(vm, vm->local_player, vm->visu.positions.local_slots,
			LOCAL_PLAYERS);
	ft_render_dragged_player(vm);
	return (0);
}
