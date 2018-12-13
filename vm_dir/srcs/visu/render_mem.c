/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:08:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 18:43:23 by ldedier          ###   ########.fr       */
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
	if (SDL_BlitScaled(vm->visu.sdl.atlas[ascii_byte].surface, NULL,
			vm->visu.sdl.w_surface, &rect) < 0)
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
