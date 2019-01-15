/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:50:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/15 17:41:21 by ldedier          ###   ########.fr       */
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
	j = ATLAS_MIN;
	while (j <= ATLAS_MAX)
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

pthread_mutex_t	mutex;

void		*ft_init_atlas_color_threaded(void *value)
{
	int				j;
	SDL_Surface		*tmp;
	char			str[2];
	t_thvar			*th;

	th = (t_thvar *)value;
	str[1] = '\0';
	j = ATLAS_MIN;
	while (j <= ATLAS_MAX)
	{
		str[0] = j;
		pthread_mutex_lock(&mutex);
		if (!(tmp = TTF_RenderText_Solid(th->font, str, th->color)))
			return (NULL);
		th->atlas[j].surface = SDL_ConvertSurface(tmp, &th->format, 0);
		pthread_mutex_unlock(&mutex);
		SDL_FreeSurface(tmp);
		j++;
	}
	return (NULL);
}

int		ft_init_atlas(t_vm *vm, t_sdl *sdl)
{
	int				i;
	SDL_Color		color;
	pthread_t		threads[MAX_PL_COLOR + 1];
	t_thvar			th[MAX_PL_COLOR + 1];

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	ft_printf("OUAI %u\n", SDL_GetTicks());
	ft_printf("%d\n", MAX_PL_COLOR);
	while (i < MAX_PL_COLOR)
	{
		th[i].font = sdl->font;
		th[i].atlas = sdl->atlas[i];
		th[i].mutex = &mutex;
		th[i].format = *sdl->surface->format;
		th[i].state = 1;
		ft_populate_sdl_color_from_int(get_color_sdl(vm->color[i]), &color);
		th[i].color = color;
		if (pthread_create(&(threads[i]), NULL,
				ft_init_atlas_color_threaded, (void *)&th[i]))
			return (1);
		i++;
	}
	th[i].font = sdl->font;
	th[i].atlas = sdl->atlas[i];
	th[i].mutex = &mutex;
	th[i].format = *sdl->surface->format;
	th[i].color = vm->visu.sdl.color;
	th[i].state = 0;
	if (pthread_create(&(threads[i]), NULL, ft_init_atlas_color_threaded, (void *)&th[i]))
		return (1);
	i = 0;
	while (i < MAX_PL_COLOR + 1)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	ft_printf("OUAI %u\n", SDL_GetTicks());
	return (0);
}
