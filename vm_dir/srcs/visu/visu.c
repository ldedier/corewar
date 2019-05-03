/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:21:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 17:27:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		process_process_visu(t_vm *vm)
{
	ft_process_delta_first(&(vm->visu.framerate));
	ft_process_events(vm);
	if ((vm->client.active && ft_process_client_events(vm)))
		vm->client.active = 0;
	if (process(vm))
	{
		clear_vm(vm);
		ft_free_all_visu(&(vm->visu));
		return (1);
	}
	if (ft_render(vm, &(vm->visu.sdl)))
	{
		clear_vm(vm);
		ft_free_all_visu(&(vm->visu));
		return (1);
	}
	ft_process_delta(&(vm->visu.framerate));
	SDL_Delay(ft_fmax(0, (1000 / (double)FRAMERATE)
				- (vm->visu.framerate.delta)));
	return (0);
}

int		process_visu(t_vm *vm)
{
	if (ft_init_all_visu(vm, &(vm->visu)))
	{
		clear_vm(vm);
		ft_free_all_visu(&(vm->visu));
		return (ft_net_error());
	}
	vm->visu.framerate.ms_counter = SDL_GetTicks();
	while (vm->visu.active)
	{
		if (process_process_visu(vm))
		{
			ft_dprintf(2, "internal malloc error\n");
			return (1);
		}
	}
	clear_vm(vm);
	ft_free_all_visu(&(vm->visu));
	return (0);
}
