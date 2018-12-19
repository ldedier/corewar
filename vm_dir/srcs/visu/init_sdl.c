/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 21:30:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_get_dimensions(t_visu *v)
{
	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	v->dim.width = dm.w;
	v->dim.height = dm.h;
}

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

SDL_Surface *ft_init_font_surface(char *str, TTF_Font *font, SDL_Color color,
		SDL_Surface *to_blit_surface)
{
	SDL_Surface *res;
	SDL_Surface *tmp;

	if (!(tmp = TTF_RenderText_Solid(font, str, color)))
		return (NULL);
	if (!(res = SDL_ConvertSurface(tmp, to_blit_surface->format, 0)))
	{
		SDL_FreeSurface(tmp);
		return (NULL);
	}
	SDL_FreeSurface(tmp);
	return (res);
}

SDL_Surface *ft_init_font_surface_sdl(char *str, t_sdl sdl)
{
	return (ft_init_font_surface(str, sdl.font, sdl.color, sdl.w_surface));
}

t_ixy	new_ixy(int x, int y)
{
	t_ixy res;

	res.x = x;
	res.y = y;
	return (res);
}


void	ft_delete_player(t_vm *vm, t_button *this, t_ixy xy)
{
	this->button_union.player->relevant = 0;
	dispatch_players(vm);
	this->visible = 0;
	ft_update_cursor(vm, xy);
}

void	nothing_on_click(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)vm;
	(void)this;
	(void)xy;
}

void	nothing_on_press(t_vm *vm, t_button *this)
{
	(void)vm;
	(void)this;
}

int		ft_render_upload_button(t_vm *vm, t_button *this)
{
	if ((vm->visu.drop_container.player == &vm->client.upload_player) ||
			(vm->client.upload_player.relevant == 1 && 
			(vm->visu.drag_container.drag_enum != DRAG_PLAYER ||
			vm->visu.drag_container.drag_union.drag_player.player
			!= &vm->client.upload_player)))
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[UL], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[UL_DISABLED], this->vscrollbar));
}

int		ft_render_download_button(t_vm *vm, t_button *this)
{
	if (!this->button_union.client_slot->downloaded)
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[DL], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[DL_DISABLED], this->vscrollbar));
}

void	ft_upload(t_vm *vm, t_button *this, t_ixy mouse)
{
	(void)this;
	(void)mouse;
	vm->client.upload_player.relevant = 0;
	vm->visu.positions.upload_slot.close.visible = 0;
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
	v->sdl.current_cursor = REGULAR;
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
	vm->visu.phase = PHASE_INIT;
	return (0);
}
