/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:17:12 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_render_server_title(t_vm *vm, double y)
{
	SDL_Rect	rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.s_title_side;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_width
		- 2 * vm->visu.center.s_title_side;
	rect.h = vm->visu.center.s_title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[SCOREWAR], NULL,
				vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	return (0);
}

int			ft_render_toolbar_buttons(t_vm *vm, t_button buttons[NB_BUTTONS])
{
	int i;

	i = 0;
	while (i < NB_ONLINE_BUTTONS)
	{
		if (buttons[i].render(vm, &buttons[i]))
			return (1);
		i++;
	}
	return (0);
}

void		ft_render_upload_link(t_vm *vm, t_xy xy)
{
	int			i;
	int			color;
	int			*pixels;
	t_player	*player;

	player = vm->visu.drag_container.drag_union.drag_player.player;
	if (vm->client.upload_player.relevant
		&& player != &vm->client.upload_player)
		color = ft_scale_color(ft_get_color(UPLOAD_COLOR), 1.3).color;
	else
		color = ft_get_player_color(vm, &vm->client.upload_player,
			UPLOAD_COLOR, 1.3);
	pixels = (int *)vm->visu.sdl.w_surface->pixels;
	i = 0;
	while (i < vm->visu.center.upload_left)
	{
		pixels[(int)xy.y * vm->visu.dim.width + i + (int)xy.x] = color;
		i++;
	}
}

int			ft_render_toolbar(t_vm *vm, double y)
{
	t_xy xy;

	xy.x = vm->visu.center.dashboard_x + vm->visu.center.upload_left;
	xy.y = y;
	ft_render_player(vm, &(vm->client.upload_player), xy, UPLOAD);
	xy.x += vm->visu.center.player_w;
	xy.y += vm->visu.center.player_h / 2;
	ft_render_upload_link(vm, xy);
	vm->visu.positions.upload_slot.close.render(vm,
		&vm->visu.positions.upload_slot.close);
	ft_render_toolbar_buttons(vm, vm->visu.buttons);
	return (0);
}
