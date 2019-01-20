/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:21:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/20 18:18:35 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		process_visu(t_vm *vm)
{
	if (ft_init_all_visu(vm, &(vm->visu)))
		return (ft_net_error());
	vm->visu.framerate.ms_counter = SDL_GetTicks();
	duel(vm, &vm->player[0], &vm->player[1]);

	ft_printf("WINNER IS %d (%s)\n", vm->winner->num, vm->winner->cor_name);
	while (vm->visu.active)
	{
		ft_process_delta_first(&(vm->visu.framerate));
		ft_process_events(vm);
		if ((vm->client.active && ft_process_client_events(vm)))
			vm->client.active = 0;
		process(vm);
		if (ft_render(vm, &(vm->visu.sdl)))
			ft_free_all_visu(&(vm->visu));
		ft_process_delta(&(vm->visu.framerate));
		ft_print_fps(&(vm->visu.framerate));
		SDL_Delay(ft_fmax(0, (1000 / (double)FRAMERATE) -
				(vm->visu.framerate.delta)));
	}
	ft_free_all_visu(&(vm->visu));
	return (0);
}
