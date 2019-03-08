/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 19:32:11 by emuckens         ###   ########.fr       */
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
	SDL_FillRect(sdl->w_surface, NULL, BACKGROUND_COL);
	ft_render_dashboard_separator(vm);
	if (ft_render_phase(vm))
		return (1);
	if (ft_render_notification(vm))
		return (1);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
