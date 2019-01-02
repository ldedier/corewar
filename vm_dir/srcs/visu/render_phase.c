/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/02 22:09:00 by ldedier          ###   ########.fr       */
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

int		ft_render_entry(t_vm *vm, char *entry, char *value, int y)
{
	SDL_Rect rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = y;
	rect.w = vm->visu.center.entry_max_w;
	rect.h = vm->visu.center.entry_h;
	if (ft_copy_str_to_surface_no_source(vm, entry, rect))
	{
		free(value);
		return (1);
	}
	rect.x = rect.x + rect.w + vm->visu.center.entry_space;
	rect.w = vm->visu.center.entry_value_max_w;
	if (ft_copy_str_to_surface_no_source(vm, value, rect))
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
		if (!(value = ft_strdup("very small")))
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

	if (!(value = ft_itoa(vm->cycle)))
		return (1);
	if (ft_render_entry(vm, "cycle", value, y))
		return (1);
	return (0);
}

int		ft_render_cycle_to_die(t_vm *vm, int y)
{
	char	*value;

	if (!(value = ft_itoa(vm->c_to_die)))
		return (1);
	if (ft_render_entry(vm, "cycle to die", value, y))
		return (1);
	return (0);
}

int		ft_render_cycle_delta(t_vm *vm, int y)
{
	char	*value;

	if (!(value = ft_itoa(CYCLE_DELTA)))
		return (1);
	if (ft_render_entry(vm, "cycle delta", value, y))
		return (1);
	return (0);
}


int		ft_render_ctd_countdown(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = 42; //NEED VARIABLE
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(vm->c_to_die)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	if (ft_render_entry(vm, "CTD countdown", value, y))
		return (1);
	return (0);
}

int		ft_render_lives_current_period(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = 42; //NEED VARIABLE
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(NBR_LIVE)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	free(tmp);
	free(tmp2);
	if (ft_render_entry(vm, "lives in current period", value, y))
		return (1);
	return (0);
}

int		ft_render_checks(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = vm->checks;
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(MAX_CHECKS)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	if (ft_render_entry(vm, "number of checks", value, y))
		return (1);
	return (0);
}

int		ft_render_play_dashboard(t_vm *vm)
{
	SDL_Rect rect;
	int y;
	int i;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = vm->visu.center.state_top;
	rect.w = 2 * vm->visu.center.dashboard_width / 3.0;
	rect.h = vm->visu.center.state_h;
	if (vm->visu.time_manager.pause)
		ft_copy_str_to_surface_no_source(vm, "Paused", rect);
	else
		ft_copy_str_to_surface_no_source(vm, "Running", rect);
	i = 0;
	y = rect.y + rect.h + vm->visu.center.state_bottom;
	while (i < NB_ENTRIES)
	{
		if (g_print_entry_value[i](vm, y))
			return (1);
		y += vm->visu.center.entry_padding;
		i++;
	}
	return (0);
}

int		ft_render_play(t_vm *vm)
{
	if (ft_render_all_process(vm))
		return (1);
	if (ft_render_memory(vm))
		return (1);
	ft_reset_metarena(vm);
	ft_render_play_dashboard(vm);
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
