/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown_hp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:25:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/20 00:34:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_background(t_vm *vm, SDL_Rect *rect)
{
	rect->x = vm->visu.center.dashboard_x + 1;
	rect->w = vm->visu.center.dashboard_width - 1;
	rect->y = vm->visu.center.live_breakdown_hp_anim_y;
	rect->h = vm->visu.center.live_breakdown_hp_anim_h;
	if (SDL_BlitScaled(vm->visu.frames[vm->visu.animation_index].background,
			NULL, vm->visu.sdl.w_surface, rect))
		return (1);
	return (0);
}

int		ft_render_magic_voldemort(t_vm *vm, SDL_Rect *rect, int *w)
{
	double		ratio;
	int			nb_live_player_1;
	int			nb_live_player_2;

	ft_get_player_lives(vm, &nb_live_player_1, &nb_live_player_2);
	ratio = get_magic_ratio(vm, nb_live_player_1, nb_live_player_2);
	if (ratio >= 0 && ratio <= 1)
		ratio = ft_flerp(vm->visu.current_hp_ratio, ratio, 0.25);
	else
		ratio = ft_flerp(vm->visu.current_hp_ratio, ratio, 0.4);
	if (!vm->visu.time_manager.pause)
		vm->visu.current_hp_ratio = ratio;
	rect->x = vm->visu.center.dashboard_x + 1 +
		vm->visu.frames[vm->visu.animation_index].voldemort_ray.x_offset;
	rect->w = ((vm->visu.frames[vm->visu.animation_index].
		harry_ray.x_offset - vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.x_offset) * ratio);
	*w = rect->w;
	if (SDL_BlitScaled(vm->visu.frames[vm->visu.animation_index].
				voldemort_ray.surface, NULL,
			vm->visu.sdl.w_surface, rect))
		return (1);
	return (0);
}

int		ft_render_magic_fight(t_vm *vm)
{
	SDL_Rect	rect;
	int			w;

	if (ft_render_background(vm, &rect))
		return (1);
	if (ft_render_magic_voldemort(vm, &rect, &w))
		return (1);
	rect.x = rect.x + w + (vm->visu.frames[vm->visu.animation_index].
		harry_ray.x_offset - vm->visu.frames[vm->visu.animation_index].
		harry_ray.screen_width) - (vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.screen_width + vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.x_offset);
	rect.w = vm->visu.center.dashboard_x + 1 +
		vm->visu.frames[vm->visu.animation_index].harry_ray.x_offset - rect.x;
	if (SDL_BlitScaled(vm->visu.frames[vm->visu.animation_index].
				harry_ray.surface, NULL,
			vm->visu.sdl.w_surface, &rect))
		return (1);
	return (0);
}

int		ft_render_live_breakdown_players(t_vm *vm)
{
	int			i;
	int			nb;
	SDL_Rect	rect;
	char		abbrev[ABBREV_LEN + 2];

	populate_hp_player_title_rect(vm, &rect);
	i = 0;
	nb = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
		{
			ft_copy_abbrev(abbrev, vm->player[i].name);
			if (ft_copy_str_to_surface_no_source(vm, abbrev, rect,
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
