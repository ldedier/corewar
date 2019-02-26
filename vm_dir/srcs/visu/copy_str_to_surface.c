/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_str_to_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:58:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/26 21:39:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_visible_char(char c)
{
	if (c >= ATLAS_MIN && c <= ATLAS_MAX)
		return (c);
	else
		return ('?');
}

int		ft_copied_char_surface_w(SDL_Rect rect, int len)
{
	return (ft_min(rect.w / len, rect.h * GLYPH_W_H_RATIO));
}

int		ft_copy_str_to_surface_no_source(t_vm *vm, char *str,
		SDL_Rect rect, int color_index)
{
	int			i;
	SDL_Rect	char_rect;
	int			len;

	char_rect.h = rect.h;
	char_rect.y = rect.y;
	char_rect.x = rect.x;
	if (!(len = ft_strlen(str)))
		return (0);
	char_rect.w = ft_copied_char_surface_w(rect, len);
	i = 0;
	while (str[i])
	{
		if (SDL_BlitScaled(vm->visu.sdl.atlas[color_index]
				[get_visible_char(str[i])].surface, NULL,
					vm->visu.sdl.w_surface, &char_rect) < 0)
		{
			return (ft_net_error());
		}
		char_rect.x += char_rect.w;
		i++;
	}
	return (0);
}

int		ft_process_copy_str_to_surface(t_vm *vm, t_ixy col_source,
			SDL_Rect *char_rect, char c)
{
	if (col_source.y < NB_SOURCES)
	{
		if (ft_blit_scaled_scrollbar(&vm->visu.sdl,
					vm->visu.sdl.atlas[col_source.x]
					[get_visible_char(c)].surface,
					*char_rect,
					vm->visu.players_list[col_source.y].vscrollbar) < 0)
			return (ft_net_error());
	}
	else
	{
		if (SDL_BlitScaled(vm->visu.sdl.atlas[col_source.x]
					[get_visible_char(c)].surface, NULL,
					vm->visu.sdl.w_surface, char_rect) < 0)
			return (ft_net_error());
	}
	return (0);
}

int		ft_copy_str_to_surface(t_vm *vm, char *str,
			SDL_Rect rect, t_ixy col_source)
{
	int			i;
	SDL_Rect	char_rect;
	int			len;

	char_rect.h = rect.h;
	char_rect.y = rect.y;
	char_rect.x = rect.x;
	if (!(len = ft_strlen(str)))
		return (0);
	char_rect.w = ft_copied_char_surface_w(rect, len);
	i = 0;
	while (str[i])
	{
		if (ft_process_copy_str_to_surface(vm, col_source, &char_rect, str[i]))
			return (1);
		char_rect.x += char_rect.w;
		i++;
	}
	return (0);
}
