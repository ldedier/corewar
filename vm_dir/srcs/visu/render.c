/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/17 22:38:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_render_horizontal_line_dashboard(t_vm *vm, int y, int col)
{
	int		i;
	int		*pix;

	pix = (int *)vm->visu.sdl.w_surface->pixels;
	i = vm->visu.center.dashboard_x;
	while (i < vm->visu.sdl.w_surface->w)
	{
		pix[y * vm->visu.sdl.w_surface->w + i] = col;
		i++;
	}
}

int		ft_blit_scaled_scrollbar(t_sdl *sdl, SDL_Surface *from,	SDL_Rect rect,
		t_vscrollbar vscrollbar)
{
	SDL_Rect	from_rect;
	int			scrolled_height;
	int			true_y;
	SDL_Surface	*tmp;
	
	if (!vscrollbar.relevant)
	{
		if (SDL_BlitScaled(from, NULL, sdl->w_surface, &rect) < 0)
			return (ft_net_error());
		return (0);
	}
	scrolled_height = (vscrollbar.compressed_height - vscrollbar.height) *
		vscrollbar.state;
	true_y = rect.y - scrolled_height;
	if (true_y > vscrollbar.pos.y + vscrollbar.height ||
		true_y + rect.h  < vscrollbar.pos.y)
		return (0);
	from_rect.w = rect.w;
	from_rect.x = 0;
	from_rect.h = ft_min(rect.h, (vscrollbar.pos.y + vscrollbar.height -
					true_y));
	from_rect.y = ft_max(0, vscrollbar.pos.y - true_y); //OK
	tmp = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_ADD);
	if (SDL_BlitScaled(from, NULL, tmp, NULL) < 0)
		return (ft_net_error());
	rect.y -= scrolled_height - from_rect.y;
	if (SDL_BlitSurface(tmp, &from_rect, sdl->w_surface, &rect) < 0)
		return (ft_net_error());
	SDL_FreeSurface(tmp);
	return (0);
}

int		ft_fill_rect_scrollbar(SDL_Surface *from, SDL_Rect *rect,
			int color, t_vscrollbar vscrollbar)
{
	SDL_Rect	from_rect;
	int			scrolled_height;
	int			true_y;

	if (!vscrollbar.relevant)
	{
		SDL_FillRect(from, rect, color);
		return (0);
	}
	scrolled_height = (vscrollbar.compressed_height - vscrollbar.height) *
		vscrollbar.state;
	true_y = rect->y - scrolled_height;
	if (true_y > vscrollbar.pos.y + vscrollbar.height ||
		true_y + rect->h  < vscrollbar.pos.y)
		return (0);
	from_rect.w = rect->w;
	from_rect.x = rect->x;
	if (vscrollbar.pos.y > true_y)
		from_rect.h = rect->h - (vscrollbar.pos.y - true_y);
	else
		from_rect.h = ft_min(rect->h, (vscrollbar.pos.y + vscrollbar.height -
			true_y));
	from_rect.y = ft_max(vscrollbar.pos.y, rect->y - scrolled_height);
	SDL_FillRect(from, &from_rect, color);
	return (0);
}

void	ft_render_lines(t_vm *vm)
{
	int		i;
	int		*pix;

	i = 0;
	pix = (int *)vm->visu.sdl.w_surface->pixels;
	while (i < vm->visu.sdl.w_surface->h)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w +
				vm->visu.center.dashboard_x)] = LINE_COL;
		i++;
	}
	ft_render_horizontal_line_dashboard(vm,
			vm->visu.center.title_h +vm->visu.center.title_top +
			vm->visu.center.title_bottom - 1, LINE_COL_DARKER);
	ft_render_horizontal_line_dashboard(vm,
			vm->visu.center.top_dashboard_height, LINE_COL);
	i = 0;
	while (i < vm->visu.center.top_dashboard_height)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w +
				vm->visu.center.dashboard_mid_x)] = LINE_COL;
		i++;
	}
}

int		ft_render_offline(t_vm *vm)
{
	(void) vm;
	return (0);
}

int		ft_render_crosses(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_render_button(vm->visu.sdl.w_surface,
					vm->visu.positions.arena_slots[i].close))
			return (ft_net_error());
		i++;
	}
	return (0);
}

double		ft_get_vscrollbar_bar_height(t_vscrollbar vscrollbar)
{
	return ((vscrollbar.height - 2 * vscrollbar.up_button.rect.h) * 
		((double)(vscrollbar.height) / ((double)vscrollbar.compressed_height)));
}

t_ixy	ft_get_vscrollbar_bar_height_y(t_vscrollbar vscrollbar)
{
	t_ixy	res;
	double	y1;
	double	y2;

	res.x = ((vscrollbar.height - 2 * vscrollbar.up_button.rect.h) * 
		((double)(vscrollbar.height) / ((double)vscrollbar.compressed_height)));
	y1 = vscrollbar.pos.y + vscrollbar.up_button.rect.h;
	y2 = vscrollbar.pos.y + vscrollbar.height -
		vscrollbar.down_button.rect.h - res.x;
	res.y = y1 + (y2 - y1) * vscrollbar.state;
	return (res);
}

int		ft_render_scrollbar_bar(t_vm *vm, t_vscrollbar vscrollbar)
{
	SDL_Rect rect;
	t_ixy height_y;

	rect.x = vscrollbar.pos.x;
	rect.w = vscrollbar.bar_width;
	height_y = ft_get_vscrollbar_bar_height_y(vscrollbar);
	rect.h = height_y.x;
	rect.y = height_y.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[SCROLL_BAR], NULL,
				vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_render_scrollbar_buttons(t_vm *vm, t_vscrollbar vscrollbar)
{
	if (ft_render_button(vm->visu.sdl.w_surface, vscrollbar.up_button))
		return (1);
	if (ft_render_button(vm->visu.sdl.w_surface, vscrollbar.down_button))
		return (1);
	return (0);
}

int		ft_render_scrollbar(t_vm *vm, t_vscrollbar vscrollbar)
{
	SDL_Rect rect;

	rect.x = vscrollbar.pos.x;
	rect.y = vscrollbar.pos.y;
	rect.w = vscrollbar.bar_width;
	rect.h = vscrollbar.height;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x777777);
	ft_render_scrollbar_bar(vm, vscrollbar);
	ft_render_scrollbar_buttons(vm, vscrollbar);
	return (0);
}

int		ft_to_print_scrollbar(t_vscrollbar vscrollbar)
{
	//	ft_printf("compressed_height: %d ; height: %d\n", vscrollbar.compressed_height, vscrollbar.height );
	return (vscrollbar.relevant &&
			vscrollbar.compressed_height > vscrollbar.height);
}

int		ft_render_vscrollbars(t_vm *vm)
{
	int i;

	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_to_print_scrollbar(vm->visu.players_list[i].vscrollbar))
			ft_render_scrollbar(vm, vm->visu.players_list[i].vscrollbar);
		i++;
	}
	return (0);
}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
	//	SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255);
	//	SDL_RenderClear(sdl->renderer);
	if (ft_render_memory(vm))
		return (1);
	ft_render_lines(vm);
	ft_render_players(vm);
	ft_render_crosses(vm);
	if (vm->client.active)
		ft_render_online(vm);
	else
		ft_render_offline(vm);
	ft_render_vscrollbars(vm);
	ft_render_dragged_player(vm);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->w_surface, NULL, BACKGROUND_COL);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
