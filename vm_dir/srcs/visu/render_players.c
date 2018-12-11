/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:47:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 20:10:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_copy_str_to_surface(t_vm *vm, SDL_Surface *surface, char *str, SDL_Rect rect)
{
	int			i;
	SDL_Rect	char_rect;
	int			len;

	char_rect.h = rect.h;
	char_rect.y = rect.y;
	char_rect.x = rect.x;
	len = ft_strlen(str);
	char_rect.w = rect.w / len;
	i = 0;
	while (str[i])
	{
		if (SDL_BlitScaled(vm->visu.sdl.atlas[(int)str[i]].surface, NULL,
				surface, &char_rect) < 0)
			return (ft_net_error());
		char_rect.x += char_rect.w;
		i++;
	}
	return (0);
}

void	ft_render_player_name(t_vm *vm, SDL_Rect player_rect, t_player player)
{
	SDL_Rect name_rect;

	name_rect.w = player_rect.w / 2;
	name_rect.h = player_rect.h / 2;
	name_rect.x = player_rect.x + player_rect.w / 4;
	name_rect.y = player_rect.y + player_rect.h / 4;
	ft_copy_str_to_surface(vm, vm->visu.sdl.w_surface, player.name, name_rect);
}

void	ft_render_player(t_vm *vm, t_player player, double x, double y)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	if (player.relevant)
	{
		SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x222222);
		ft_render_player_name(vm, rect, player);
	}
	else
		SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x444444);
}

void	ft_render_title(t_vm *vm, int title_index, double x, double y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.dashboard_mid_width -
		2 * vm->visu.center.title_side;
	rect.h = vm->visu.center.title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[title_index], NULL, vm->visu.sdl.w_surface, &rect) < 0)
		ft_net_error();
}

void	ft_render_player_pool(t_vm *vm, t_player players[MAX_PLAYERS],
			double x_offset, int title_index)
{
	int		i;
	double	y;

	y = vm->visu.center.title_top;
	ft_render_title(vm, title_index, x_offset + vm->visu.center.title_side, y);
	y += vm->visu.center.title_h + vm->visu.center.title_bottom;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, players[i],
			x_offset + vm->visu.center.player_left, y);
		y += vm->visu.center.player_h + vm->visu.center.player_padding;
		i++;
	}
}

int		ft_render_players(t_vm *vm)
{
	ft_render_player_pool(vm, vm->player, vm->visu.center.dashboard_x,
			BATTLEFIELD);
	ft_render_player_pool(vm, vm->local_player,
		vm->visu.center.dashboard_mid_x, LOCAL_PLAYERS);
	return (0);
}
