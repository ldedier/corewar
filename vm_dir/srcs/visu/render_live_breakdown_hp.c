/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live_breakdown_hp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:25:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/04 21:18:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** return the player1 / player2 live ratio
*/

double	get_magic_ratio(int lives_player_1, int lives_player_2)
{
	if (!lives_player_1 && !lives_player_2)
		return (0.5);
	else
		return ((double)lives_player_1 /
			(double)(lives_player_1 + lives_player_2));
}

int		ft_moy(int val1, int val2)
{
	return ((val1 + val2) / 2);
}

int		ft_render_magic_fight(t_vm *vm)
{
	SDL_Rect	rect;
	double		ratio;

	rect.x = vm->visu.center.dashboard_x + 1;
	rect.w = vm->visu.center.dashboard_width - 1;
	rect.y = vm->visu.center.live_breakdown_hp_anim_y;
	rect.h = vm->visu.center.live_breakdown_hp_anim_h;

	static int nb_live_player_1 = 0;
	static int nb_live_player_2 = 0;
	static int i = 0;
	static int val = 2;
	static int pola = 0;

	ratio = get_magic_ratio(nb_live_player_1, nb_live_player_2);
	
	if (i < exp(val))
		i++;
	else
	{
		i = 0;
		pola = !pola;
		val++;
	}
	if (pola)
		nb_live_player_1++;
	else
		nb_live_player_2++;
	if (SDL_BlitScaled(vm->visu.frames[vm->visu.animation_index].background,
			NULL, vm->visu.sdl.w_surface, &rect))
		return (1);

	int	diff_x = (vm->visu.frames[vm->visu.animation_index].harry_ray.x_offset -
		vm->visu.frames[vm->visu.animation_index].harry_ray.screen_width) - 
		(vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.screen_width + vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.x_offset);

	rect.x = vm->visu.center.dashboard_x + 1 +
		vm->visu.frames[vm->visu.animation_index].voldemort_ray.x_offset;

	int v_w_2 = ((vm->visu.frames[vm->visu.animation_index].
		harry_ray.x_offset - vm->visu.frames[vm->visu.animation_index].
		voldemort_ray.x_offset) * ratio);
	
	rect.w = v_w_2;
	if (SDL_BlitScaled(vm->visu.frames[vm->visu.animation_index].
				voldemort_ray.surface, NULL,
			vm->visu.sdl.w_surface, &rect))
		return (1);
	rect.x = rect.x + rect.w + diff_x;
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
