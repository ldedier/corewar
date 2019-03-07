/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_alts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 21:15:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 17:15:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_render_write(t_vm *vm, int pc)
{
	SDL_Rect		rect;
	t_color_manager	cm;
	double			altval;

	rect = get_rect_from_pc(vm, pc);
	altval = (double)vm->metarena[pc].write_fade / (double)ALT_COLOR_VALUE;
	cm = ft_interpolate_color(ALT_COLOR, BACKGROUND_COL, altval);
	rect.x--;
	rect.w += 2;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, cm.color);
}
