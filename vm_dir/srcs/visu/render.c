/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/09 14:02:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_memory(t_vm *vm)
{
	int			i;
	int			j;
	SDL_Surface	*mem_surface;
	SDL_Surface	*byte_surface;
	SDL_Rect	rect;

	rect.w = 100;
	rect.h = 150;
	rect.x = 0;
	rect.y = 0;
	if (!(mem_surface = SDL_CreateRGBSurface(0, vm->visu.mem.w, vm->visu.mem.h,
			32, 0, 0, 0, 0)))
		return (1);
	i = 0;
	while (i * MEM_COLS < MEM_SIZE)
	{
		j = 0;
		while (j < MEM_COLS)
		{
			if (!(byte_surface = TTF_RenderText_Solid(vm->visu.sdl.font,
					"00", vm->visu.sdl.color)))
				return  (1);
		//	ft_printf("%d %d \n", byte_surface->w, byte_surface->h);
			if (SDL_BlitSurface(byte_surface, NULL, mem_surface, NULL) < 0) //protect
				return (ft_net_error());
			j++;
		}
		i++;
	}
	if (SDL_BlitSurface(mem_surface, NULL, vm->visu.sdl.w_surface, NULL) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
//	SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255);
//	SDL_RenderClear(sdl->renderer);
	if (ft_render_memory(vm))
		return (1);
	//	ft_render_players(client);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->surface, NULL, 0);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
