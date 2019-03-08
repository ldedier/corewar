/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:47:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 17:17:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_render_fade(t_vm *vm, int pc)
{
	SDL_Rect		rect;
	t_color_manager	cm;

	cm = ft_interpolate_color(vm->metarena[pc].death_color, BACKGROUND_COL,
			(double)vm->metarena[pc].death_fade / (double)MAX_FADE);
	rect = get_rect_from_pc(vm, pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, cm.color);
}
