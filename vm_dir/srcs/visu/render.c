/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 14:26:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_print_byte_composant(t_vm *vm, double *x_dist, double y_dist,
			int byte)
{
	int			ascii_byte;
	SDL_Rect	rect;

	rect.w = vm->visu.center.glyph_width;
	rect.h = vm->visu.center.glyph_height;
	rect.x = *x_dist;
	rect.y = y_dist;

	if (byte < 10)
		ascii_byte = byte + '0';
	else
		ascii_byte = byte + 'a' - 10;
	if (SDL_BlitScaled(vm->visu.sdl.atlas[ascii_byte], NULL, vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	*x_dist += vm->visu.center.glyph_width;
	return (0);
}

int		ft_print_byte(t_vm *vm, int byte, double *x_dist, double y_dist)
{
	if (ft_print_byte_composant(vm, x_dist, y_dist, (byte / 16) % 16))
		return (1);
	*x_dist += vm->visu.center.x_diff_byte;
	if (ft_print_byte_composant(vm, x_dist, y_dist, byte % 16))
		return (1);
	return (0);
}

int		ft_render_memory(t_vm *vm)
{
	int			i;
	int			j;
	double		x_dist;
	double		y_dist;

	i = 0;
	y_dist = vm->visu.center.top_margin;
	while (i * MEM_COLS < MEM_SIZE)
	{
		j = 0;
		x_dist = vm->visu.center.left_margin;
		while (j < MEM_COLS)
		{
			if (i * MEM_COLS + j < MEM_SIZE)
			{
				if (ft_print_byte(vm, (unsigned char)vm->arena[i * MEM_COLS + j],
						&x_dist, y_dist))
					return (1);
				x_dist += vm->visu.center.x_diff;
			}
			j++;
		}
		y_dist += vm->visu.center.glyph_height + vm->visu.center.y_diff;
		i++;
	}
	return (0);
}

void	ft_render_lines(t_vm *vm)
{
	int		i;
	int		*pix;

	i = 0;
	pix = (int *)vm->visu.sdl.w_surface->pixels;
	while (i < vm->visu.sdl.w_surface->h)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w + vm->visu.center.dashboard_x)] = 0xffffff;
		i++;
	}
	i = vm->visu.center.dashboard_x;
	while (i < vm->visu.sdl.w_surface->w)
	{
		pix[(int)(vm->visu.center.dashboard_mid_y * vm->visu.sdl.w_surface->w + i)] = 0xffffff;
		i++;
	}
	i = 0;
	while (i < vm->visu.center.dashboard_mid_y)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w + vm->visu.center.dashboard_mid_x)] = 0xffffff;
		i++;
	}
}

void	ft_render_player(t_vm *vm, t_player player, double x_offset, double *y)
{
	SDL_Rect rect;

	(void)player;
	rect.x = x_offset + vm->visu.center.player_left;
	rect.y = *y;
	rect.w = vm->visu.center.player_w;
	rect.h = vm->visu.center.player_h;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x222222);

	*y += vm->visu.center.player_h + vm->visu.center.player_padding;
}

void	ft_render_title(t_vm *vm, int title_index, double x_offset, double *y)
{
	SDL_Rect	rect;

	rect.x = x_offset + vm->visu.center.title_side;
	rect.y = *y;
	rect.w = vm->visu.center.dashboard_mid_width -
		2 * vm->visu.center.title_side;
	rect.h = vm->visu.center.title_h;
	if (SDL_BlitScaled(vm->visu.sdl.titles[title_index], NULL, vm->visu.sdl.w_surface, &rect) < 0)
		ft_net_error();
	*y += vm->visu.center.title_h + vm->visu.center.title_bottom;
}

void	ft_render_player_pool(t_vm *vm, t_player players[MAX_PLAYERS],
			double x_offset, int title_index)
{
	int		i;
	double	y;

	y = vm->visu.center.title_top;
	ft_render_title(vm, title_index, x_offset, &y);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, players[i], x_offset, &y);
		i++;
	}
}


void	ft_render_players(t_vm *vm)
{
	ft_render_player_pool(vm, vm->player, vm->visu.center.dashboard_x,
			BATTLEFIELD);
	ft_render_player_pool(vm, vm->local_player,
		vm->visu.center.dashboard_mid_x, LOCAL_PLAYERS);
}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
	//	SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255);
	//	SDL_RenderClear(sdl->renderer);
	if (ft_render_memory(vm))
		return (1);
	ft_render_lines(vm);
	ft_render_players(vm);
	//	ft_render_players(client);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->w_surface, NULL, 0x333333);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
