/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:21:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/04 16:24:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_process_events(t_vm *vm)
{
	(void)vm;
}

void    ft_render(t_vm *vm, t_sdl *sdl)
{
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);
//	ft_render_board(client);
//	ft_render_players(client);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->surface, NULL, 0);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
}

int process_visu(t_vm *vm)
{
	if (ft_init_all_sdl(&(vm->visu)))
		return (1);
	vm->visu.framerate.ms_counter = SDL_GetTicks();
	while (vm->visu.active)
	{
		ft_process_delta_first(&(vm->visu.framerate));
		ft_process_events(vm);
		ft_render(vm, &(vm->visu.sdl));
		ft_process_delta(&(vm->visu.framerate));
		SDL_Delay(ft_fmax(0, (1000 / FRAMERATE) - (vm->visu.framerate.delta)));
	}
	return (0);
}
