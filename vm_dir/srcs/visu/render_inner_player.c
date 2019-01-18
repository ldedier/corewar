/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inner_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:05:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 19:05:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_render_inner_name_value(t_vm *vm, SDL_Rect inner_rect,
		t_player *player, t_player_source source)
{
	SDL_Rect	name_rect;
	t_ixy		col_source;
	char		abbrev[ABBREV_LEN + 2];

	name_rect.w = 3 * inner_rect.w / 8;
	name_rect.h = inner_rect.h / 3;
	name_rect.x = inner_rect.x + 7 * (inner_rect.w / 16);
	name_rect.y = inner_rect.y + inner_rect.h / 12;
	col_source.y = source;
	if (source % NB_SOURCES == ARENA)
		col_source.x = player->color.index;
	else
		col_source.x = MAX_PL_COLOR;
	ft_copy_abbrev(abbrev, player->name);
	ft_copy_str_to_surface(vm, abbrev, name_rect, col_source);
}

void	ft_render_inner_name(t_vm *vm, SDL_Rect inner_rect, t_player *player,
		t_player_source source)
{
	SDL_Rect	name_rect;
	t_ixy		col_source;

	name_rect.w = 3 * inner_rect.w / 16;
	name_rect.h = inner_rect.h / 3;
	name_rect.x = inner_rect.x + inner_rect.w / 16;
	name_rect.y = inner_rect.y + inner_rect.h / 12;
	col_source.y = source;
	col_source.x = MAX_PL_COLOR;
	ft_copy_str_to_surface(vm, "name", name_rect, col_source);
	ft_render_inner_name_value(vm, inner_rect, player, source);
}

int		ft_render_inner_number_value(t_vm *vm, SDL_Rect inner_rect,
			t_player *player, t_player_source source)
{
	SDL_Rect	name_rect;
	t_ixy		col_source;
	char		*number_to_str;

	name_rect.w = 3 * inner_rect.w / 8;
	name_rect.h = inner_rect.h / 3;
	name_rect.x = inner_rect.x + 7 * (inner_rect.w / 16);
	name_rect.y = inner_rect.y + 7 * inner_rect.h / 12;
	col_source.y = source;
	col_source.x = MAX_PL_COLOR;
	if (!(number_to_str = ft_itoa(player->num)))
		return (1);
	ft_copy_str_to_surface(vm, number_to_str, name_rect, col_source);
	free(number_to_str);
	return (0);
}

int		ft_render_inner_number(t_vm *vm, SDL_Rect inner_rect, t_player *player,
		t_player_source source)
{
	SDL_Rect	name_rect;
	t_ixy		col_source;

	name_rect.w = 3 * inner_rect.w / 16;
	name_rect.h = inner_rect.h / 3;
	name_rect.x = inner_rect.x + inner_rect.w / 16;
	name_rect.y = inner_rect.y + 7 * inner_rect.h / 12;
	col_source.y = source;
	col_source.x = MAX_PL_COLOR;
	ft_copy_str_to_surface(vm, "number", name_rect, col_source);
	if (ft_render_inner_number_value(vm, inner_rect, player, source))
		return (1);
	return (0);
}

void	ft_render_inner_name_full(t_vm *vm, SDL_Rect player_rect,
			t_player *player, t_player_source source)
{
	SDL_Rect	name_rect;
	t_ixy		col_source;
	char		abbrev[ABBREV_LEN + 2];
	int			len;
	int			abbrev_len;

	name_rect.w = player_rect.w / 2;
	name_rect.h = player_rect.h / 2;
	name_rect.y = player_rect.y + player_rect.h / 4;
	col_source.y = source;
	if (source % NB_SOURCES == ARENA)
		col_source.x = player->color.index;
	else
		col_source.x = MAX_PL_COLOR;
	ft_copy_abbrev(abbrev, player->name);
	abbrev_len = ft_strlen(abbrev);
	len = ft_copied_char_surface_w(name_rect, abbrev_len) * abbrev_len;
	name_rect.x = player_rect.x + (player_rect.w - len) / 2.0;
	ft_copy_str_to_surface(vm, abbrev, name_rect, col_source);
}
