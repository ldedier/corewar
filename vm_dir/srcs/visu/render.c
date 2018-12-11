/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 17:32:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_render_lines(t_vm *vm)
{
	int		i;
	int		*pix;

	i = 0;
	pix = (int *)vm->visu.sdl.w_surface->pixels;
	while (i < vm->visu.sdl.w_surface->h)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w + vm->visu.center.dashboard_x)] = 0xffffff;
		i++;
	}
	i = vm->visu.center.dashboard_x;
	while (i < vm->visu.sdl.w_surface->w)
	{
		pix[(int)(vm->visu.center.dashboard_mid_y * vm->visu.sdl.w_surface->w + i)] = 0xffffff;
		i++;
	}
	i = 0;
	while (i < vm->visu.center.dashboard_mid_y)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w + vm->visu.center.dashboard_mid_x)] = 0xffffff;
		i++;
	}
}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
	//	SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255);
	//	SDL_RenderClear(sdl->renderer);
	if (ft_render_memory(vm))
		return (1);
	ft_render_lines(vm);
	ft_render_players(vm);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->w_surface, NULL, 0x333333);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
