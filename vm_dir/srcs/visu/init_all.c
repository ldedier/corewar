/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:48:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 21:49:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_init_all_visu(t_vm *vm, t_visu *v)
{
	ft_init_sdl_to_null(v);
	if (ft_init_sdl(v))
		return (1);
	if (!(v->sdl.font = ft_load_font(PATH"/resources/mana.ttf", 1000)))
		return (1);
	v->sdl.color.r = 255;
	v->sdl.color.g = 255;
	v->sdl.color.b = 255;
	v->sdl.color.a = 255;
	if (ft_init_atlas(vm, &(v->sdl)))
		return (1);
	if (ft_init_textures(v))
		return (1);
	if (ft_init_cursors(v))
		return (1);
	v->react.w_scale = (double)v->dim.width / 2560.0;
	v->react.h_scale = (double)v->dim.height / 1440.0;
	ft_init_center(v, &(v->center));
	ft_init_players_list(v);
	ft_init_vscrollbars_compressed_size(vm, v);
	ft_populate_slots_positions(vm, v);
	ft_init_buttons(vm, v);
	v->event_manager.enable_mouse_up = 1;
	v->event_manager.pressed_button = NULL;
	v->drag_container.drag_union.drag_player.player = NULL;
	v->drop_container.player = NULL;
	v->drag_container.parent = v;
	ft_init_crosses(vm);
	if (vm->client.active)
	{
		ft_init_client_slot_surface(vm);
		ft_update_download_buttons_client_rect(vm);
	}
	SDL_SetCursor(v->sdl.cursor_packers[REGULAR].cursor);
	v->sdl.current_cursor = REGULAR;
	vm->visu.phase = PHASE_INIT;
	return (0);
}
