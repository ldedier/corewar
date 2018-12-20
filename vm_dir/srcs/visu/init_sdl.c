/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 21:47:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_init_sdl_to_null(t_visu *v)
{
	int i;
	int j;

	v->sdl.window = NULL;
	v->sdl.renderer = NULL;
	v->sdl.w_surface = NULL;
	v->sdl.font = NULL;
	i = 0;
	while (i < MAX_PL_COLOR)
	{
		j = 0;
		while (j < NB_GLYPHS)
		{
			v->sdl.atlas[i][j].surface = NULL;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < NB_TITLES)
		v->sdl.titles[i++] = NULL;
}

int		ft_init_sdl_2(t_visu *v)
{
	if (!(v->sdl.renderer = SDL_CreateRenderer(v->sdl.window, -1, 0)))
		return (1);
	if (SDL_RenderSetLogicalSize(v->sdl.renderer,
				v->sdl.screen.w, v->sdl.screen.h) < 0)
		return (1);
	if (SDL_SetRenderDrawColor(v->sdl.renderer, 0, 0, 0, 255) < 0)
		return (1);
	if (!(v->sdl.w_surface = SDL_CreateRGBSurface(0,
					v->dim.width, v->dim.height, 32, 0, 0, 0, 0)))
		return (1);
	if (!(v->sdl.surface = SDL_CreateRGBSurface(0,
				v->dim.width, v->dim.height, 32, 0, 0, 0, 0)))
		return (1);
	return (0);
}

int		ft_init_sdl(t_visu *v)
{
	v->sdl.screen.x = 300;
	v->sdl.screen.y = 200;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (1);
	if (TTF_Init() < 0)
		return (1);
	ft_get_dimensions(v);
	v->sdl.screen.w = v->dim.width;
	v->sdl.screen.h = v->dim.height;
	if (!(v->sdl.window = SDL_CreateWindow("corewar visu",
					v->sdl.screen.x, v->sdl.screen.y, v->sdl.screen.w, v->sdl.screen.h,
					SDL_WINDOW_FULLSCREEN_DESKTOP)))
		return (1);
	if (ft_init_sdl_2(v))
		return (1);
	return (0);
}

int		ft_init_all_sdl(t_vm *vm, t_visu *v)
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
