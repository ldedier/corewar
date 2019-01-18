/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_visu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:07:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 20:14:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_free_surface(SDL_Surface *surface)
{
	if (surface != NULL)
		SDL_FreeSurface(surface);
}

void	ft_free_font(TTF_Font *font)
{
	if (font != NULL)
		TTF_CloseFont(font);
}

void	ft_free_surfaces(t_visu *v)
{
	int i;

	i = 0;
	while (i < NB_IMAGES)
	{
		ft_free_surface(v->sdl.images[i]);
		i++;
	}
	i = 0;
	while (i < NB_TITLES)
	{
		ft_free_surface(v->sdl.titles[i]);
		i++;
	}
	while (i < NB_FRAMES)
	{
		ft_free_surface(v->frames[i].harry_ray.surface);
		ft_free_surface(v->frames[i].voldemort_ray.surface);
		ft_free_surface(v->frames[i].background);
		i++;
	}
}

void	ft_free_atlas(t_visu *v)
{
	int i;
	int j;

	i = 0;
	while (i < MAX_PL_COLOR)
	{
		j = ATLAS_MIN;
		while (j <= ATLAS_MAX)
		{
			ft_free_surface(v->sdl.atlas[i][j].surface);
			j++;
		}
		i++;
	}
}

void	ft_free_cursors(t_visu *v)
{
	int i;

	i = 0;
	while (i < NB_CURSORS)
	{
		ft_free_surface(v->sdl.cursor_packers[i].surface);
		SDL_FreeCursor(v->sdl.cursor_packers[i].cursor);
		i++;
	}
}
