/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_visu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:07:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 20:12:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_free_all_visu(t_visu *v)
{
	ft_free_surfaces(v);
	ft_free_font(v->sdl.font);
	ft_free_atlas(v);
	ft_free_cursors(v);
	ft_lstdel_value(&v->downloaded_players);
	if (v->sdl.w_surface)
		SDL_FreeSurface(v->sdl.w_surface);
	if (v->sdl.renderer)
		SDL_DestroyRenderer(v->sdl.renderer);
	if (v->sdl.window)
		SDL_DestroyWindow(v->sdl.window);
	if (TTF_WasInit())
		TTF_Quit();
	if (SDL_WasInit(SDL_INIT_EVERYTHING))
		SDL_Quit();
}
