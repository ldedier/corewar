/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/10 00:21:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_reset_metarena(t_vm *vm)
{
	t_list		*ptr;
	t_process	*process;

	ptr = vm->proc;
	while (ptr != NULL)
	{
		process = (t_process *)(ptr->content);
		vm->metarena[process->pc].process_color_index = 0;
		ptr = ptr->next;
	}
}

void	ft_render_play_lines(t_vm *vm)
{
	 ft_render_horizontal_line_dashboard(vm, vm->visu.center.game_entries_h,
		LINE_COL);
	 ft_render_horizontal_line_dashboard(vm, vm->visu.center.game_entries_h +
			vm->visu.center.player_entries_h, LINE_COL);
	
	if (vm->nb_players != 2)
		ft_render_horizontal_line_dashboard(vm, vm->visu.center.game_entries_h +
			vm->visu.center.list_player_entries_h, LINE_COL);
	else
		ft_render_horizontal_line_dashboard(vm,
			vm->visu.center.live_breakdown_hp_y, LINE_COL);
}

int		ft_render_dashboard(t_vm *vm)
{
	ft_render_play_lines(vm);
	if (ft_render_entries(vm))
		return (1);
	if (ft_render_player_entries(vm))
		return (1);
	if (vm->nb_players != 2)
	{	
		if (ft_render_live_breakdown(vm))
			return (1);
	}
	else
	{
		if (ft_render_live_breakdown_hp(vm))
			return (1);
	}
	if (ft_render_play_footer(vm))
		return (1);
	return (0);
}

int		ft_render_play(t_vm *vm)
{
	static double anim_rest = 0;

	if (ft_render_all_dead_process(vm))
		return (1);
	if (ft_render_all_process(vm))
		return (1);
	if (ft_render_all_lives(vm))
		return (1);
	if (ft_render_memory(vm))
		return (1);
	ft_reset_metarena(vm);
	if (ft_render_dashboard(vm))
		return (1);
	if (!vm->visu.time_manager.pause)
	{
		anim_rest += ft_fclamp(0.25,
			vm->visu.time_manager.cycles_per_turn * 0.025, 1);
		vm->visu.animation_index = (int)(vm->visu.animation_index + anim_rest)
			% NB_FRAMES;
		if (anim_rest > 1)
			anim_rest -= (int)anim_rest;
	}
	return (0);
}
