/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:21:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 18:33:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
		ft_print_fps(&(vm->visu.framerate));
		SDL_Delay(ft_fmax(0, (1000 / FRAMERATE) - (vm->visu.framerate.delta)));
	}
	return (0);
}
