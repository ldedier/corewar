/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/16 23:53:07 by ldedier          ###   ########.fr       */
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
		vm->visu.center.title_h +vm->visu.center.title_top + vm->visu.center.title_bottom , LINE_COL_DARKER);
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

int		ft_render_scrollbar(t_vm *vm, t_vscrollbar vscrollbar)
{
	SDL_Rect rect;

	rect.x = vscrollbar.pos.x;
	rect.y = vscrollbar.pos.y;
	rect.w = vscrollbar.bar_width;
	rect.h = vscrollbar.height;

	SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x777777);
	return (0);
}

int		ft_render_vscrollbars(t_vm *vm)
{
	int i;

	i = 0;
	while (i < NB_SOURCES)
	{
		if (vm->visu.players_list[i].vscrollbar.relevant)
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
