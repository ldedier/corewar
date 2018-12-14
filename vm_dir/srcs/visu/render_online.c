/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 16:56:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_render_server_title(t_vm *vm, double y)
{
	SDL_Rect    rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.s_title_side;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_width -
		2 * vm->visu.center.s_title_side;
	rect.h = vm->visu.center.s_title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[SCOREWAR], NULL,
				vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	return (0);
}

int			ft_render_button(SDL_Surface *logo, SDL_Surface *to, t_button button)
{
	if (SDL_BlitScaled(logo, NULL,
				to, &(button.rect)) < 0)
		return (ft_net_error());
	return (0);
}

int			ft_render_buttons(t_vm *vm, t_button buttons[NB_BUTTONS])
{
	ft_render_button(vm->visu.sdl.images[UL], vm->visu.sdl.w_surface,
		buttons[UPLOAD_BUTTON]);
	ft_render_button(vm->visu.sdl.images[SORT_ALPHA], vm->visu.sdl.w_surface,
		buttons[ALPHA_SORT_BUTTON]);
	ft_render_button(vm->visu.sdl.images[SORT_SCORE], vm->visu.sdl.w_surface,
		buttons[SCORE_SORT_BUTTON]);
	return (0);
}

int			ft_render_toolbar(t_vm *vm, double y)
{
	t_xy xy;
	xy.x = vm->visu.center.dashboard_x + vm->visu.center.upload_left;
	xy.y = y;
	ft_render_player(vm, &(vm->client.upload_player), xy, ARENA);
	//xy.x += vm->visu.center.player_w;
	//draw buttons
	ft_render_buttons(vm, vm->visu.sdl.buttons);
//	ft_printf("OUAI\n");
	return (0);
}

int			ft_render_server_players(t_vm *vm, double y)
{
	(void)vm;
	(void)y;
	return (0);
}

int			ft_render_online(t_vm *vm)
{
	double y;

	y = vm->visu.center.top_dashboard_height + vm->visu.center.title_top;
	if (ft_render_server_title(vm, y))
		return (1);
	y += vm->visu.center.s_title_h + vm->visu.center.title_bottom;
	if (ft_render_toolbar(vm, y))
		return (1);
	y += vm->visu.center.player_h + 4200; //OLALA
	if (ft_render_server_players(vm, y))
		return (1);
	return (0);
}
