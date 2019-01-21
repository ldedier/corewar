/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:48:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 23:29:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_init_sdl_utils(t_vm *vm, t_visu *v)
{
	v->sdl.color.r = 255;
	v->sdl.color.g = 255;
	v->sdl.color.b = 255;
	v->sdl.color.a = 255;
	if (!(v->sdl.font = ft_load_font(PATH"/resources/mana.ttf", 1000)))
		return (1);
	if (ft_init_atlas(vm, &(v->sdl)))
		return (1);
	if (ft_init_textures(v))
		return (1);
	if (ft_init_cursors(v))
		return (1);
	return (0);
}

int		ft_init_positions(t_vm *vm, t_visu *v)
{
	v->react.w_scale = (double)v->dim.width / 2560.0;
	v->react.h_scale = (double)v->dim.height / 1440.0;
	ft_init_center(v, &(v->center));
	ft_init_players_list(vm, v);
	ft_init_vscrollbars_compressed_size(vm, v);
	ft_populate_slots_positions(vm, v);
	ft_init_buttons(vm, v);
	return (0);
}

void	set_number_downloaded_players(t_vm *vm)
{
	t_list		*ptr;
	t_player	*player;

	ptr = vm->visu.downloaded_players;
	while (ptr != NULL)
	{
		player = ptr->content;
		player->num = vm->nb;
		ptr = ptr->next;
	}
}

void	ft_init_others(t_vm *vm, t_visu *v)
{
	set_number_downloaded_players(vm);
	v->event_manager.enable_mouse_up = 1;
	v->event_manager.pressed_button = NULL;
	v->drag_container.drag_union.drag_player.player = NULL;
	v->drop_container.player = NULL;
	v->drag_container.parent = v;
	if (vm->client.active)
		ft_update_download_buttons_client_rect(vm);
	v->time_manager.pause = 0;
	v->time_manager.cycles_per_turn = INIT_CYCLES_PER_TURN;
	ft_init_crosses(vm);
	SDL_SetCursor(v->sdl.cursor_packers[REGULAR].cursor);
	v->sdl.current_cursor = REGULAR;
	vm->visu.phase = PHASE_INIT;
	if (vm->nb_players)
		vm->visu.local_type = LOCAL_LOCAL;
	else
		vm->visu.local_type = LOCAL_DOWNLOAD;
	vm->cycle = 0;
	v->sort_cs_func = &ft_sort_alpha_cs;
	v->inv_sort = 0;
	vm->visu.notification.image_index = -1;
	vm->visu.animation_index = 0;
	vm->visu.current_hp_ratio = 0.5;
}

int		ft_init_all_visu(t_vm *vm, t_visu *v)
{
	ft_bzero(v, sizeof(t_visu));
	v->active = 1;
	if (ft_init_sdl(v))
		return (1);
	if (ft_init_sdl_utils(vm, v))
		return (1);
	if (ft_parse_player_folder(PATH"/downloads", &vm->visu.downloaded_players))
		return (1);
	ft_lst_mergesort(&vm->visu.downloaded_players, ft_sort_alpha, 0);
	if (ft_init_positions(vm, v))
		return (1);
	if (ft_init_hp_surface(&vm->visu))
		return (1);
	ft_init_others(vm, v);
	return (0);
}
