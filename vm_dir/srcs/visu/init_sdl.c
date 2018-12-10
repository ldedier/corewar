/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:58:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/05 14:32:05 by ldedier          ###   ########.fr       */
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
	v->sdl.window = NULL;
	v->sdl.renderer = NULL;
	v->sdl.w_surface = NULL;
	v->sdl.font = NULL;
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

int		ft_init_all_sdl(t_visu *v)
{
	ft_init_sdl_to_null(v);
	if (ft_init_sdl(v))
		return (1);
	if (!(v->sdl.font = ft_load_font(PATH"/resources/workaholic.ttf", 80)))
		return (1);
	v->sdl.color.r = 255;
	v->sdl.color.g = 255;
	v->sdl.color.b = 255;
	v->sdl.color.a = 100;
	v->react.w_scale = (double)v->dim.width / 2560.0;
	v->react.h_scale = (double)v->dim.height / 1440.0;
	v->mem.x = 0;
	v->mem.y = 0;
	v->mem.w = v->dim.width;
	v->mem.h = v->dim.height;
	return (0);
}
