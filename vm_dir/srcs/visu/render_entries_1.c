/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entries_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:42:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 22:01:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int (*g_print_entry_value[NB_ENTRIES])(t_vm *, int y) = {
	ft_render_cycles_per_second,
	ft_render_cycle,
	ft_render_ctd_countdown,
	ft_render_lives_current_period,
	ft_render_checks,
	ft_render_cycle_to_die,
	ft_render_cycle_delta
};

int		ft_render_entry(t_vm *vm, char *entry, char *value, int y)
{
	SDL_Rect rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = y;
	rect.w = vm->visu.center.entry_max_w;
	rect.h = vm->visu.center.entry_h;
	if (ft_copy_str_to_surface_no_source(vm, entry, rect, MAX_PL_COLOR))
	{
		free(value);
		return (1);
	}
	rect.x = rect.x + rect.w + vm->visu.center.entry_space;
	rect.w = vm->visu.center.entry_value_max_w;
	if (ft_copy_str_to_surface_no_source(vm, value, rect, MAX_PL_COLOR))
	{
		free(value);
		return (1);
	}
	free(value);
	return (0);
}

int		ft_render_cycles_per_second(t_vm *vm, int y)
{
	char	*value;
	double	val;

	val = vm->visu.time_manager.cycles_per_turn * FRAMERATE;
	if (val < 1)
	{
		if (!(value = ft_strdup("1")))
			return (1);
	}
	else
	{
		if (!(value = ft_itoa(val)))
			return (1);
	}
	if (ft_render_entry(vm, "cycles per second", value, y))
		return (1);
	return (0);
}

int		ft_render_cycle(t_vm *vm, int y)
{
	char	*value;

	if (!(value = ft_itoa(vm->total_cycle)))
		return (1);
	if (ft_render_entry(vm, "cycle", value, y))
		return (1);
	return (0);
}

int		ft_render_entries(t_vm *vm)
{
	SDL_Rect	rect;
	int			y;
	int			i;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = vm->visu.center.state_top;
	rect.w = 2 * vm->visu.center.dashboard_width / 3.0;
	rect.h = vm->visu.center.state_h;
	if (vm->visu.time_manager.pause)
		ft_copy_str_to_surface_no_source(vm, "Paused", rect, MAX_PL_COLOR);
	else
		ft_copy_str_to_surface_no_source(vm, "Running", rect, MAX_PL_COLOR);
	i = 0;
	y = rect.y + rect.h + vm->visu.center.state_bottom;
	while (i < NB_ENTRIES)
	{
		if (g_print_entry_value[i](vm, y))
			return (1);
		y += vm->visu.center.entry_padding + vm->visu.center.entry_h;
		i++;
	}
	return (0);
}
