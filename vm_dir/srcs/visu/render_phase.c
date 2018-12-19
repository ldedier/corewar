/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:54 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 19:07:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_init_offline(t_vm *vm)
{
	(void) vm;
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
	if (vm->visu.buttons[FIGHT_BUTTON].render(vm,
			&vm->visu.buttons[FIGHT_BUTTON]))
		return (1);
	ft_render_dragged_player(vm);
	return (0);
}

int		ft_render_play(t_vm *vm)
{
	(void)vm;
	return (0);
}

int		ft_render_end(t_vm *vm)
{
	(void)vm;
	return (0);
}

int		ft_render_phase(t_vm *vm)
{
	if (vm->visu.phase == PHASE_INIT)
		return (ft_render_init(vm));
	else if (vm->visu.phase == PHASE_PLAY)
		return (ft_render_play(vm));
	else
		return (ft_render_end(vm));
}
