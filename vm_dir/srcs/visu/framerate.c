/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:15:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/08/26 15:15:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_process_delta_first(t_framerate *framerate)
{
	framerate->previous = SDL_GetPerformanceCounter();
}

void	ft_process_delta(t_framerate *framerate)
{
	framerate->current = SDL_GetPerformanceCounter();
	framerate->delta = (double)(((framerate->current - framerate->previous) *
			1000)) / SDL_GetPerformanceFrequency();
}

void	ft_print_fps(t_framerate *framerate)
{
	if (SDL_GetTicks() - framerate->ms_counter > 1000)
	{
		framerate->ms_counter = SDL_GetTicks();
		printf("fps : %d (%d)\n", ft_min(60, framerate->fps_counter), framerate->fps_counter);
		//printf("fps : %d\n", framerate->fps_counter);
		framerate->fps_counter = 0;
	}
}
