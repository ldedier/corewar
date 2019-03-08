/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_activity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:57:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 17:11:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_render_process_instruction(t_vm *vm, int pc, int color)
{
	int			i;
	SDL_Rect	rect;

	i = 1;
	rect = get_rect_from_pc(vm, pc);
	ft_draw_rect_surface(vm->visu.sdl.w_surface, rect, color);
	while (i < vm->metarena[pc].ins_len)
	{
		rect = get_rect_from_pc(vm, pc + i);
		ft_draw_rect_surface(vm->visu.sdl.w_surface, rect, color);
		i++;
	}
}

void	ft_render_process(t_vm *vm, int pc)
{
	SDL_Rect		rect;
	int				color;

	color = vm->metarena[pc].process_color;
	rect = get_rect_from_pc(vm, pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, color);
	ft_render_process_instruction(vm, pc, color);
	if (vm->metarena[pc].process_carry)
	{
		rect.x++;
		rect.y++;
		rect.w -= 2;
		rect.h -= 2;
		ft_draw_rect_surface(vm->visu.sdl.w_surface, rect, 0xffffff);
	}
}
