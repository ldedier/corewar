/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 19:08:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_crosses(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->visu.positions.arena_slots[i].close.render(vm,
			&vm->visu.positions.arena_slots[i].close))
			return (ft_net_error());
		i++;
	}
	return (0);
}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
	if (ft_render_phase(vm))
		return (1);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->w_surface, NULL, BACKGROUND_COL);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
