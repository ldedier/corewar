/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:08:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 20:04:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

SDL_Rect	get_rect_from_pc(t_vm *vm, int pc)
{
	SDL_Rect	res;
	int			x;
	int			y;

	x = pc % MEM_COLS;
	y = pc / MEM_COLS;
	res.w = vm->visu.center.glyph_width * 2 + vm->visu.center.x_diff_byte
		+ vm->visu.center.x_diff;
	res.h = vm->visu.center.glyph_height + vm->visu.center.y_diff;
	res.x = vm->visu.center.left_margin + x * (vm->visu.center.glyph_width * 2
			+ vm->visu.center.x_diff_byte + vm->visu.center.x_diff)
		- vm->visu.center.x_diff / 2.0;
	res.y = vm->visu.center.top_margin + y
		* (vm->visu.center.glyph_height + vm->visu.center.y_diff)
		- vm->visu.center.y_diff / 2.0;
	return (res);
}

void		ft_draw_rect_surface(SDL_Surface *surface, SDL_Rect rect, int color)
{
	int		x;
	int		y;
	int		*pix;

	pix = surface->pixels;
	x = rect.x;
	while (x <= rect.x + rect.w)
	{
		pix[rect.y * surface->w + x] = color;
		pix[(rect.y + rect.h) * surface->w + x] = color;
		x++;
	}
	y = rect.y;
	while (y <= rect.y + rect.h)
	{
		pix[y * surface->w + rect.x] = color;
		pix[y * surface->w + rect.x + rect.w] = color;
		y++;
	}
}

int			ft_print_byte_composant(t_vm *vm, t_xy *dist, int pc, int byte)
{
	int			ascii_byte;
	SDL_Rect	rect;
	int			color_index;

	rect.w = vm->visu.center.glyph_width;
	rect.h = vm->visu.center.glyph_height;
	rect.x = dist->x;
	rect.y = dist->y;
	if (byte < 10)
		ascii_byte = byte + '0';
	else
		ascii_byte = byte + 'a' - 10;
	if (vm->metarena[pc].process_color != -1)
		color_index = 0;
	else
		color_index = vm->metarena[pc].content_color_index;

//	ft_printf("color index: %d ascii byte: %d\n", color_index, ascii_byte);
	if (SDL_BlitScaled(
				vm->visu.sdl.atlas[color_index][ascii_byte].surface, NULL,
				vm->visu.sdl.w_surface, &rect) < 0)
	{
		return (ft_net_error());
	}
	dist->x += vm->visu.center.glyph_width;
	return (0);
}

int			ft_print_byte(t_vm *vm, int pc, t_xy *dist)
{	
	int byte;

	if (vm->visu.phase == PHASE_PLAY)
	{
		if (vm->metarena[pc].live_fade)
			ft_render_live(vm, pc);
		else if (vm->metarena[pc].process_color != -1)
			ft_render_process(vm, pc);
		else if (vm->metarena[pc].write_fade)
			ft_render_write(vm, pc);
		else if (vm->metarena[pc].death_fade)
			ft_render_fade(vm, pc);
		if (!vm->visu.time_manager.pause)
		{
			if (vm->metarena[pc].write_fade)
				vm->metarena[pc].write_fade--;
			if (vm->metarena[pc].live_fade)
				vm->metarena[pc].live_fade--;
			if (vm->metarena[pc].death_fade)
				vm->metarena[pc].death_fade--;
		}
	}
	byte = vm->arena[pc];
	if (ft_print_byte_composant(vm, dist, pc, (byte & 0xF0) >> 4))
		return (1);
	dist->x += vm->visu.center.x_diff_byte;
	if (ft_print_byte_composant(vm, dist, pc, byte & 0xF))
		return (1);
	return (0);
}

int			ft_render_memory(t_vm *vm)
{
	int			i;
	int			j;
	t_xy		dist;

	i = -1;
	dist.y = vm->visu.center.top_margin;
	while ((++i) * MEM_COLS < MEM_SIZE)
	{
		j = 0;
		dist.x = vm->visu.center.left_margin;
		while (j < MEM_COLS)
		{
			if (i * MEM_COLS + j < MEM_SIZE)
			{

				if (ft_print_byte(vm, i * MEM_COLS + j, &dist))
					return (1);
				dist.x += vm->visu.center.x_diff;
			}
			j++;
		}
		dist.y += vm->visu.center.glyph_height + vm->visu.center.y_diff;
	}
	return (0);
}
