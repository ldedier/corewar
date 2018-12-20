/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:50:21 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 20:57:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_populate_sdl_color_from_int(int color, SDL_Color *sdl_color)
{
	t_color_manager col;

	col = ft_get_color(color);
	sdl_color->r = col.r;
	sdl_color->g = col.g;
	sdl_color->b = col.b;
}

int		ft_init_atlas_color(t_sdl *sdl, int i, SDL_Color color)
{
	int				j;
	SDL_Surface		*tmp;
	char			str[2];

	str[1] = '\0';
	j = 33;
	while (j < 126)
	{
		str[0] = j;
		if (!(tmp = TTF_RenderText_Solid(sdl->font, str, color)))
			return (1);
		sdl->atlas[i][j].surface = SDL_ConvertSurface(tmp,
				sdl->w_surface->format, 0);
		SDL_FreeSurface(tmp);
		j++;
	}
	return (0);
}

int		ft_init_atlas(t_vm *vm, t_sdl *sdl)
{
	int				i;
	SDL_Color		color;

	i = 0;
	while (i < MAX_PL_COLOR)
	{
		ft_populate_sdl_color_from_int(get_color_sdl(vm->color[i]), &color);
		if (ft_init_atlas_color(sdl, i, color))
			return (1);
		i++;
	}
	if (ft_init_atlas_color(sdl, i, vm->visu.sdl.color))
		return (1);
	return (0);
}
