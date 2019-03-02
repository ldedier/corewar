/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:23:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/02 21:40:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_populate_breakdown_bar(t_vm *vm, SDL_Rect *rect)
{
	rect->x = vm->visu.center.dashboard_x +
		vm->visu.center.live_breakdown_bar_left;
	rect->w = vm->visu.center.live_breakdown_bar_w;
	rect->h = vm->visu.center.live_breakdown_bar_h;
	rect->y = vm->visu.center.game_entries_h +
		vm->visu.center.list_player_entries_h +
		vm->visu.center.live_breakdown_bar_top;
}

int		ft_process_render_live_breakdown_bar(t_vm *vm, SDL_Rect *rect,
			double *from, t_ixy i_sum)
{
	if (vm->player[i_sum.x].relevant)
	{
		rect->x = vm->visu.center.dashboard_x +
			vm->visu.center.live_breakdown_bar_left + *from;
		if (!i_sum.y)
			rect->w = vm->visu.center.live_breakdown_bar_w /
				(double)vm->nb_players;
		else
			rect->w = vm->visu.center.live_breakdown_bar_w *
				vm->player[i_sum.x].live / (double)i_sum.y;
		*from += rect->w;
		if (SDL_FillRect(vm->visu.sdl.w_surface, rect,
				vm->player[i_sum.x].color.value))
			return (1);
	}
	return (0);
}

int		ft_render_live_breakdown_bar(t_vm *vm)
{
	double		from;
	SDL_Rect	rect;
	t_ixy		i_sum;

	ft_populate_breakdown_bar(vm, &rect);
	from = 0;
	i_sum.x = 0;
	i_sum.y = get_live_sum(vm);
	while (i_sum.x < MAX_PLAYERS)
	{
		if (ft_process_render_live_breakdown_bar(vm, &rect, &from, i_sum))
			return (1);
		i_sum.x++;
	}
	rect.x = vm->visu.center.dashboard_x +
		vm->visu.center.live_breakdown_bar_left;
	rect.w = vm->visu.center.live_breakdown_bar_w;
	if (SDL_BlitScaled(vm->visu.sdl.images[BREAKDOWN_BAR],
			NULL, vm->visu.sdl.w_surface, &rect))
		return (1);
	return (0);
}

int		ft_render_live_breakdown_title(t_vm *vm, SDL_Rect rect)
{
	if (ft_copy_str_to_surface_no_source(vm,
		"live breakdown for current period", rect, 0))
		return (1);
	return (0);
}

int		ft_render_live_breakdown(t_vm *vm)
{
	SDL_Rect rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = vm->visu.center.game_entries_h +
		vm->visu.center.list_player_entries_h +
			vm->visu.center.live_breakdown_title_top;
	rect.w = vm->visu.center.live_breakdown_title_w;
	rect.h = vm->visu.center.live_breakdown_title_h;
	if (ft_render_live_breakdown_title(vm, rect))
		return (1);
	if (ft_render_live_breakdown_bar(vm))
		return (1);
	return (0);
}
