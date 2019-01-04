/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/03 15:38:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_init_offline(t_vm *vm)
{
	(void) vm;
	return (0);
}

int		ft_render_offline_buttons(t_vm *vm, t_button buttons[NB_BUTTONS])
{
	int i;

	i = NB_ONLINE_BUTTONS;
	while (i < NB_BUTTONS - 1)
	{
		if (buttons[i].render(vm, &buttons[i]))
			return (1);
		i++;
	}
	return (0);
}

int		ft_render_init(t_vm *vm)
{
	if (ft_render_memory(vm))
		return (1);
	ft_render_init_lines(vm);
	ft_render_players(vm);
	ft_render_crosses(vm);
	if (vm->client.active)
		ft_render_init_online(vm);
	else
		ft_render_init_offline(vm);
	ft_render_vscrollbars(vm);
	ft_render_offline_buttons(vm, vm->visu.buttons);
	ft_render_dragged_player(vm);
	return (0);
}

int		ft_render_phase(t_vm *vm)
{
	if (vm->visu.phase == PHASE_INIT)
		return (ft_render_init(vm));
	else
		return (ft_render_play(vm));
}
