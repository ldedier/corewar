/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown_hp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:25:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/04 05:24:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_magic_fight(t_vm *vm)
{
	SDL_Rect bgrect;

	bgrect.x = vm->visu.center.dashboard_x + 1;
	bgrect.w = vm->visu.center.dashboard_width - 1;
	bgrect.y = vm->visu.center.live_breakdown_hp_anim_y;
	bgrect.h = vm->visu.center.live_breakdown_hp_anim_h;
	if (SDL_BlitScaled(vm->visu.frames[0].background, NULL,
			vm->visu.sdl.w_surface, &bgrect))
		return (1);
	return (0);
}

int		ft_render_live_breakdown_players(t_vm *vm)
{
	int			i;
	int			nb;
	SDL_Rect	rect;

	rect.x = vm->visu.center.dashboard_x +
		vm->visu.center.live_breakdown_hp_players_side;
	rect.y = vm->visu.center.live_breakdown_hp_y +
		vm->visu.center.live_breakdown_hp_title_top +
			vm->visu.center.live_breakdown_title_h +
				vm->visu.center.live_breakdown_hp_title_bottom;
	rect.w = vm->visu.center.entry_max_w;
	rect.h = vm->visu.center.live_breakdown_hp_players_h;
	i = 0;
	nb = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
		{
			if (ft_copy_str_to_surface_no_source(vm, vm->player[i].name, rect,
					vm->player[i].color.index))
				return (1);
			rect.x += rect.w + vm->visu.center.live_breakdown_hp_players_side;
			rect.w = vm->visu.dim.width - rect.x;
			if (nb++)
				return (0);
		}
		i++;
	}
	return (1);
}

int		ft_render_live_breakdown_hp(t_vm *vm)
{
	SDL_Rect rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = vm->visu.center.live_breakdown_hp_y +
		vm->visu.center.live_breakdown_hp_title_top;
	rect.w = vm->visu.center.live_breakdown_title_w;
	rect.h = vm->visu.center.live_breakdown_title_h;
	if (ft_render_live_breakdown_title(vm, rect))
		return (1);
	if (ft_render_live_breakdown_players(vm))
		return (1);
	if (ft_render_magic_fight(vm))
		return (1);
	return (0);
}
