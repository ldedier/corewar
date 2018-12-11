/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:58:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 18:58:10 by ldedier          ###   ########.fr       */
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

	v->sdl.window = NULL;
	v->sdl.renderer = NULL;
	v->sdl.w_surface = NULL;
	v->sdl.font = NULL;
	i = 0;
	while (i < NB_GLYPHS)
		v->sdl.atlas[i++].surface = NULL;
	i = 0;
	while (i < NB_TITLES)
		v->sdl.titles[i++] = NULL;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->sdl.names[i] = NULL;
		i++;
	}
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

int		ft_init_atlas(t_sdl *sdl)
{
	int				i;
	char			str[2];
	SDL_Surface		*tmp;

	str[1] = '\0';
	i = 33;
	while (i < 126)
	{
		str[0] = i;
		if (!(tmp = TTF_RenderText_Solid(sdl->font,
				str, sdl->color)))
			return (1);
		sdl->atlas[i].surface = SDL_ConvertSurface(tmp,
			sdl->w_surface->format, 0);
		if (TTF_GlyphMetrics(sdl->font, i, &(sdl->atlas[i].minx),
			&(sdl->atlas[i].maxx), &(sdl->atlas[i].miny), &(sdl->atlas[i].maxy),
				&(sdl->atlas[i].advance)) == -1)
			return (ft_net_error());
		SDL_FreeSurface(tmp);
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
	if(!(res = SDL_ConvertSurface(tmp, to_blit_surface->format, 0)))
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
			ft_init_font_surface_sdl("battlefield:", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[LOCAL_PLAYERS] = 
			ft_init_font_surface_sdl("local players:", visu->sdl)))
		return (1);
	return (0);
}

void	ft_init_center(t_visu *visu, t_center *c)
{
	c->dashboard_x = DASHBOARD_X * visu->react.w_scale;
	c->dashboard_mid_y = DASHBOARD_MID_Y * visu->react.h_scale;
	c->dashboard_mid_width = ((visu->dim.width - DASHBOARD_X) / 2.0) * visu->react.w_scale;
	c->dashboard_mid_x = c->dashboard_x + c->dashboard_mid_width;
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

	c->title_top = TITLE_BORDER_TOP * visu->react.h_scale;
	c->title_bottom = TITLE_BORDER_BOTTOM * visu->react.h_scale;
	c->title_side = TITLE_BORDER_SIDE * visu->react.w_scale;
	c->title_h = TITLE_HEIGHT * visu->react.h_scale;

	c->player_left = PLAYER_BORDER_LEFT * visu->react.w_scale;
	c->player_right = PLAYER_BORDER_RIGHT * visu->react.w_scale;
	c->player_padding = PLAYER_PADDING * visu->react.h_scale;
	c->player_bottom = PLAYER_BORDER_BOTTOM * visu->react.h_scale;

	c->player_w = (visu->dim.width - c->dashboard_mid_x) - (c->player_left + c->player_right);

	c->player_h = (c->dashboard_mid_y - (double)(c->title_top + c->title_h +
			c->title_bottom + ((MAX_PLAYERS - 1) * c->player_padding) +
			c->player_bottom)) / (double) MAX_PLAYERS;

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
//	printf("%f %f \n", c->glyph_width, c->glyph_height);
//	printf("%f %f \n", c->player_w, c->player_h);
}

int		ft_init_all_sdl(t_visu *v)
{
	ft_init_sdl_to_null(v);
	if (ft_init_sdl(v))
		return (1);
	//if (!(v->sdl.font = ft_load_font(PATH"/resources/kongtext.ttf", 1000)))
	if (!(v->sdl.font = ft_load_font(PATH"/resources/mana.ttf", 1000)))
		return (1);
//	if (!(v->sdl.font = ft_load_font(PATH"/resources/mana.ttf", 80)))
//		return (1);
	v->sdl.color.r = 255;
	v->sdl.color.g = 255;
	v->sdl.color.b = 255;
	v->sdl.color.a = 255;
	if (ft_init_atlas(&(v->sdl)))
		return (1);
	if (ft_init_textures(v))
		return (1);
	v->react.w_scale = (double)v->dim.width / 2560.0;
	v->react.h_scale = (double)v->dim.height / 1440.0;
	ft_init_center(v, &(v->center));
	v->mem.x = 0;
	v->mem.y = 0;
	v->mem.w = v->dim.width;
	v->mem.h = v->dim.height;
	return (0);
}
