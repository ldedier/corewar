/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:40:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:04:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_get_dimensions(t_visu *v)
{
	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	v->dim.width = dm.w;
	v->dim.height = dm.h;
}

SDL_Surface	*ft_init_font_surface(char *str, TTF_Font *font, SDL_Color color,
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

SDL_Surface	*ft_init_font_surface_sdl(char *str, t_sdl sdl)
{
	return (ft_init_font_surface(str, sdl.font, sdl.color, sdl.w_surface));
}

t_ixy		new_ixy(int x, int y)
{
	t_ixy res;

	res.x = x;
	res.y = y;
	return (res);
}

int			ft_is_in_rect(t_ixy xy, SDL_Rect rect)
{
	return (xy.x > rect.x && xy.x < rect.x + rect.w &&
			xy.y > rect.y && xy.y < rect.y + rect.h);
}
