/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:46:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 17:01:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_render_live(t_vm *vm, int pc)
{
	SDL_Rect		rect;

	rect = get_rect_from_pc(vm, pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, vm->metarena[pc].live_color);
}
