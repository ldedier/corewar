/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:59:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 18:59:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_blit_scaled_scrollbar(t_sdl *sdl, SDL_Surface *from,	SDL_Rect rect,
		t_vscrollbar vscrollbar)
{
	SDL_Rect	from_rect;
	int			scrolled_height;
	int			true_y;
	SDL_Surface	*tmp;
	
	if (!vscrollbar.relevant)
	{
		if (SDL_BlitScaled(from, NULL, sdl->w_surface, &rect) < 0)
			return (ft_net_error());
		return (0);
	}
	scrolled_height = ft_get_scrolled_height(vscrollbar);
	true_y = rect.y - scrolled_height;
	if (true_y > vscrollbar.pos.y + vscrollbar.height ||
		true_y + rect.h  < vscrollbar.pos.y)
		return (0);
	from_rect.w = rect.w;
	from_rect.x = 0;
	from_rect.h = ft_min(rect.h, (vscrollbar.pos.y + vscrollbar.height -
					true_y));
	from_rect.y = ft_max(0, vscrollbar.pos.y - true_y); //OK
	tmp = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	if (from != sdl->images[CLOSE]  && from != sdl->images[DL]
			&& from != sdl->images[DL_DISABLED])
		SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_ADD);
	if (SDL_BlitScaled(from, NULL, tmp, NULL) < 0)
		return (ft_net_error());
	rect.y -= scrolled_height - from_rect.y;
	if (SDL_BlitSurface(tmp, &from_rect, sdl->w_surface, &rect) < 0)
		return (ft_net_error());
	SDL_FreeSurface(tmp);
	return (0);
}

int		ft_fill_rect_scrollbar(SDL_Surface *from, SDL_Rect *rect,
			int color, t_vscrollbar vscrollbar)
{
	SDL_Rect	from_rect;
	int			scrolled_height;
	int			true_y;

	if (!vscrollbar.relevant)
	{
		SDL_FillRect(from, rect, color);
		return (0);
	}
	scrolled_height = ft_get_scrolled_height(vscrollbar);
	true_y = rect->y - scrolled_height;
	if (true_y > vscrollbar.pos.y + vscrollbar.height ||
		true_y + rect->h  < vscrollbar.pos.y)
		return (0);
	from_rect.w = rect->w;
	from_rect.x = rect->x;
	if (vscrollbar.pos.y > true_y)
		from_rect.h = rect->h - (vscrollbar.pos.y - true_y);
	else
		from_rect.h = ft_min(rect->h, (vscrollbar.pos.y + vscrollbar.height -
			true_y));
	from_rect.y = ft_max(vscrollbar.pos.y, rect->y - scrolled_height);
	SDL_FillRect(from, &from_rect, color);
	return (0);
}
