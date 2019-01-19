/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:06:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 19:13:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_closing_cross(t_vm *vm, t_xy xy)
{
	SDL_Rect	cross_rect;

	cross_rect.w = vm->visu.center.cross_border;
	cross_rect.h = vm->visu.center.cross_border;
	cross_rect.x = xy.x + vm->visu.center.player_w -
			vm->visu.center.cross_border;
	cross_rect.y = xy.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[CLOSE], NULL,
			vm->visu.sdl.w_surface, &cross_rect) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_get_player_color_no_drag(t_vm *vm, t_player *player,
			int initial_color, float value)
{
	t_color_manager c;

	if (player != vm->visu.drop_container.player ||
			player == vm->visu.drag_container.drag_union.drag_player.player ||
				vm->visu.drag_container.drag_enum != DRAG_PLAYER)
		return (initial_color);
	else
	{
		c = ft_get_color(initial_color);
		return (ft_scale_color(c, value).color);
	}
}

int		ft_get_player_color(t_vm *vm, t_player *player, int initial_color,
			float value)
{
	t_color_manager c;

	if (player != vm->visu.drop_container.player ||
		vm->visu.drag_container.drag_enum != DRAG_PLAYER)
		return (initial_color);
	else
	{
		c = ft_get_color(initial_color);
		return (ft_scale_color(c, value).color);
	}
}

void	ft_copy_abbrev(char *abbrev, char *str)
{
	int i;

	i = 0;
	while (str[i] && i < ABBREV_LEN)
	{
		abbrev[i] = str[i];
		i++;
	}
	if (i > 0 && ft_isseparator(str[i - 1]))
		i--;
	if (str[i])
		abbrev[i++] = '.';
	abbrev[i] = '\0';
}

int		ft_render_title(t_vm *vm, int title_index, double x, double y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_mid_width -
		2 * vm->visu.center.title_side;
	rect.h = vm->visu.center.title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[title_index],
			NULL, vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	return (0);
}
