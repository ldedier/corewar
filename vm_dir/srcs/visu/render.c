/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:02:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/10 19:13:27 by ldedier          ###   ########.fr       */
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

}

int		ft_render(t_vm *vm, t_sdl *sdl)
{
	//	SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255);
	//	SDL_RenderClear(sdl->renderer);
	if (ft_render_memory(vm))
		return (1);
	ft_render_lines(vm);
	//	ft_render_players(client);
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->w_surface);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FillRect(sdl->w_surface, NULL, 0x333333);
	SDL_DestroyTexture(sdl->texture);
	SDL_RenderPresent(sdl->renderer);
	vm->visu.framerate.fps_counter++;
	return (0);
}
