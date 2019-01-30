/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_alts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 21:15:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/30 17:16:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_render_alt(t_vm *vm, int pc, int value)
{
	SDL_Rect		rect;
	t_color_manager	cm;

	rect = get_rect_from_pc(vm, pc);
	cm = ft_interpolate_color(0xffffff, BACKGROUND_COL, value /
		(double)ALT_COLOR_VALUE);
	rect.x--;
	rect.w += 2;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, cm.color);
	if (!vm->visu.time_manager.pause)
		vm->metarena[pc].alt_color--;
}

void	ft_render_alt_colors(t_vm *vm)
{
	int i;
	int j;
	int value;

	i = -1;
	while ((++i) * MEM_COLS < MEM_SIZE)
	{
		j = 0;
		while (j < MEM_COLS)
		{
			if (i * MEM_COLS + j < MEM_SIZE)
			{
				if ((value = vm->metarena[i * MEM_COLS + j].alt_color))
					ft_render_alt(vm, i * MEM_COLS + j, value);
			}
			j++;
		}
	}
}
