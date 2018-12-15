/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/14 18:34:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

TTF_Font    *ft_load_font(char *str, int quality)
{
	TTF_Font *font;

	font = TTF_OpenFont(str, quality);
	if (font == NULL)
		ft_net_error();
	return (font);
}

SDL_Surface *ft_load_image(char *str)
{
	SDL_Surface *surface;

	if (!(surface = IMG_Load(str)))
		ft_net_error();
	return (surface);
}

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
	while (i < MAX_PL_COL)
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

void	ft_populate_sdl_color_from_int(int color, SDL_Color *sdl_color)
{
	t_color_manager col;

	col = ft_get_color(color);
	sdl_color->r = col.r;
	sdl_color->g = col.g;
	sdl_color->g = col.b;
}

int		ft_init_atlas(t_vm *vm, t_sdl *sdl)
{
	int				i;
	int				j;
	char			str[2];
	SDL_Surface		*tmp;
	SDL_Color		color;

	str[1] = '\0';
	i = 0;
	while (i < MAX_PL_COL)
	{
		ft_populate_sdl_color_from_int(color_on(vm->color, i, SDL), &color);
		j = 33;
		while (j < 126)
		{
			str[0] = j;
			if (!(tmp = TTF_RenderText_Solid(sdl->font,
							str, color)))
				return (1);
			sdl->atlas[i][j].surface = SDL_ConvertSurface(tmp,
					sdl->w_surface->format, 0);
			SDL_FreeSurface(tmp);
			j++;
		}
		i++;
	}
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

int		ft_init_textures(t_visu *visu)
{
	if (!(visu->sdl.titles[BATTLEFIELD] =
			ft_init_font_surface_sdl("battlefield", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[LOCAL_PLAYERS] =
			ft_init_font_surface_sdl("local players", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[SCOREWAR] =
			ft_init_font_surface_sdl("Scorewar server", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[UPLOAD_HERE] =
			ft_init_font_surface_sdl("upload slot", visu->sdl)))
		return (1);
	if (!(visu->sdl.images[CLOSE] = ft_load_image(PATH"/resources/close.png")))
		return (1);
	if (!(visu->sdl.images[DL] = ft_load_image(PATH"/resources/download.png")))
		return (1);
	if (!(visu->sdl.images[UL] = ft_load_image(PATH"/resources/upload.png")))
		return (1);
	if (!(visu->sdl.images[SORT_ALPHA] =
			ft_load_image(PATH"/resources/alpha_sort.png")))
		return (1);
	if (!(visu->sdl.images[SORT_SCORE] =
			ft_load_image(PATH"/resources/score_sort.png")))
		return (1);
	return (0);
}

void	ft_init_center_memory(t_visu *visu, t_center *c)
{
	c->left_margin = MEM_BORDER_LEFT * visu->react.w_scale;
	c->right_margin = MEM_BORDER_RIGHT * visu->react.w_scale;
	c->top_margin = MEM_BORDER_TOP * visu->react.h_scale;
	c->bottom_margin = MEM_BORDER_BOTTOM * visu->react.h_scale;
	c->x_diff = X_DIFF * visu->react.w_scale;
	c->x_diff_byte = X_DIFF_BYTE * visu->react.w_scale;
	c->y_diff = Y_DIFF * visu->react.h_scale;
	c->nb_cols = MEM_COLS;
	c->nb_lines = ft_round((double)((double)MEM_SIZE /
				(double)MEM_COLS));

	while ((c->y_diff * (c->nb_lines - 1) > visu->dim.height
				- c->top_margin - c->bottom_margin) &&
			c->y_diff > 0)
		c->y_diff--;
	while ((c->x_diff * (c->nb_cols - 1) > 
				c->dashboard_x - 2 * c->nb_cols *
				c->x_diff_byte) && c->x_diff > 0)
		c->x_diff--;
	c->glyph_width = (c->dashboard_x - c->left_margin - c->right_margin -
			(c->nb_cols - 1) * c->x_diff - c->nb_cols * c->x_diff_byte) / ((double)
				(2 * c->nb_cols));
	c->glyph_height = (visu->dim.height - c->top_margin - c->bottom_margin -
			(c->nb_lines - 1) * c->y_diff) / ((double) c->nb_lines);
}

void	ft_init_center_players(t_visu *visu, t_center *c)
{
	c->title_top = TITLE_BORDER_TOP * visu->react.h_scale;
	c->title_bottom = TITLE_BORDER_BOTTOM * visu->react.h_scale;
	c->title_side = TITLE_BORDER_SIDE * visu->react.w_scale;
	c->title_h = TITLE_HEIGHT * visu->react.h_scale;

	c->player_left = PLAYER_BORDER_LEFT * visu->react.w_scale;
	c->player_right = PLAYER_BORDER_RIGHT * visu->react.w_scale;
	c->player_padding = PLAYER_PADDING * visu->react.h_scale;
	c->player_bottom = PLAYER_BORDER_BOTTOM * visu->react.h_scale;

	c->player_inner_border = PLAYER_INNER_BORDER * ft_fmin(visu->react.w_scale, visu->react.h_scale);
	c->cross_border = CROSS_BORDER * ft_fmin(visu->react.w_scale, visu->react.h_scale);
	c->player_w = (visu->dim.width - c->dashboard_mid_x) - (c->player_left + c->player_right);
	c->player_h = (c->top_dashboard_height - (double)(c->title_top + c->title_h +
				c->title_bottom + ((MAX_PLAYERS - 1) * c->player_padding) +
				c->player_bottom)) / (double) MAX_PLAYERS;
}

void	ft_init_center_online(t_visu *visu, t_center *c)
{
	c->s_title_side = S_TITLE_SIDE * visu->react.w_scale;
	c->s_title_h = S_TITLE_HEIGHT * visu->react.h_scale;

	c->upload_left = UPLOAD_LEFT * visu->react.w_scale;
	c->upload_right = UPLOAD_RIGHT * visu->react.w_scale;
	c->sort_padding = SORT_PADDING * visu->react.w_scale;
	c->sort_score_right = SORT_SCORE_RIGHT * visu->react.w_scale;
	c->toolbar_blank = c->dashboard_width - ((c->player_h * 3) + c->player_w +
			c->upload_right + c->upload_left + c->sort_padding +
				c->sort_score_right);
}

void	ft_init_center(t_visu *visu, t_center *c)
{
	c->dashboard_x = DASHBOARD_X * visu->react.w_scale;
	c->top_dashboard_height = TOP_DASHBOARD_HEIGHT * visu->react.h_scale;
	c->dashboard_width = (visu->dim.width - DASHBOARD_X * visu->react.w_scale);
	c->dashboard_mid_width = c->dashboard_width / 2.0;
	c->dashboard_mid_x = c->dashboard_x + c->dashboard_mid_width;

	ft_init_center_memory(visu, c);
	ft_init_center_players(visu, c);
	ft_init_center_online(visu, c);
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

void	ft_populate_closing_button(t_vm *vm, t_button *button,
			t_player *player, t_ixy xy)
{
	button->rect.x = xy.x;
	button->rect.y = xy.y;
	button->rect.w = vm->visu.center.cross_border;
	button->rect.h = vm->visu.center.cross_border;
	button->surface = vm->visu.sdl.images[CLOSE];
	button->button_union.player = player;
	button->on_click = &ft_delete_player;
	button->visible = 0;
}

void	ft_populate_upload_slot(t_vm *vm, t_visu *v)
{
	t_ixy xy;

	v->positions.upload_slot.player.x = v->center.dashboard_x +
		v->center.upload_left;
	v->positions.upload_slot.player.y = v->center.top_dashboard_height +
		v->center.title_top + v->center.s_title_h +
			v->center.title_bottom;

	xy.x = v->positions.upload_slot.player.x + v->center.player_w -
			v->center.cross_border;
	xy.y = v->positions.upload_slot.player.y;

	ft_populate_closing_button(vm,
		&(v->positions.upload_slot.close), &vm->client.upload_player, xy);
}

void    ft_populate_slots_positions(t_vm *vm, t_visu *v)
{
	int		i;
	double	y;
	t_ixy	xy;

	y = v->center.title_top;
	y += v->center.title_h + v->center.title_bottom;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->positions.arena_slots[i].player.x = v->center.dashboard_x +
			v->center.player_left;
		v->positions.arena_slots[i].player.y = y;
		xy.x = v->positions.arena_slots[i].player.x +
				v->center.player_w - v->center.cross_border;
		xy.y = y;
		ft_populate_closing_button(vm, &(v->positions.arena_slots[i].close),
			&(vm->player[i]), xy);
		v->positions.local_slots[i].player.x = v->center.dashboard_mid_x +
			v->center.player_left;
		v->positions.local_slots[i].player.y = y;
		y += v->center.player_h + v->center.player_padding;
		i++;
	}
	ft_populate_upload_slot(vm, v);
}

int		ft_populate_cursor(t_cursor_packer *cp, char *str, int hot_x, int hot_y)
{
	if (!(cp->surface = ft_load_image(str)))
		return (1);
	if (!(cp->cursor = SDL_CreateColorCursor(cp->surface, hot_x,
			hot_y)))
	{
		//free ?
		return (1);
	}
	return (0);
}

int		ft_init_cursors(t_visu *v)
{
	if (ft_populate_cursor(&(v->sdl.cursor_packers[GRAB]), PATH"/resources/grab.png", 7, 3))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[DRAGGABLE]), PATH"/resources/draggable.png", 7, 5))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[CLICK]), PATH"/resources/click.png", 5, 0))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[REGULAR]), PATH"/resources/regular.png", 0, 0))
		return (1);
	return (0);
}

void	nothing(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)vm;
	(void)this;
	(void)xy;
	ft_printf("hehehe\n");
}

void	ft_init_button(t_button *button, SDL_Rect rect, SDL_Surface *surface,
			void (*on_click)(t_vm *, t_button *, t_ixy xy))
{
	button->rect = rect;
	button->surface = surface;
	button->on_click = on_click;
	button->visible = 1;
}

void	ft_init_buttons(t_vm *vm, t_visu *visu)
{
	SDL_Rect	rect;

	rect.w = visu->center.player_h;
	rect.h = visu->center.player_h;
	rect.x = visu->center.dashboard_x + visu->center.upload_left +
		visu->center.player_w + visu->center.upload_right;
	rect.y =  visu->center.top_dashboard_height + visu->center.s_title_h +
		visu->center.title_bottom + visu->center.title_top;

	ft_init_button(&(visu->sdl.buttons[UPLOAD_BUTTON]), rect,
		vm->visu.sdl.images[UL], &nothing);

	rect.x += visu->center.player_h + visu->center.toolbar_blank;

	ft_init_button(&(visu->sdl.buttons[ALPHA_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_ALPHA], &nothing);
	
	rect.x += visu->center.player_h + visu->center.sort_padding;

	ft_init_button(&(visu->sdl.buttons[SCORE_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_SCORE], &nothing);
}

void	ft_init_crosses(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			vm->visu.positions.arena_slots[i].close.visible = 1;
		i++;
	}
}

int		ft_init_all_sdl(t_vm *vm, t_visu *v)
{
	ft_init_sdl_to_null(v);
	if (ft_init_sdl(v))
		return (1);
	//if (!(v->sdl.font = ft_load_font(PATH"/resources/kongtext.ttf", 1000)))
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
	ft_populate_slots_positions(vm, v);
	ft_init_buttons(vm, v);
	v->sdl.current_cursor = REGULAR;
	v->event_manager.enable_mouse_up = 1;
	v->drag_container.player = NULL;
	v->drop_container.player = NULL;
	ft_init_crosses(vm);
	SDL_SetCursor(v->sdl.cursor_packers[REGULAR].cursor);
	return (0);
}
