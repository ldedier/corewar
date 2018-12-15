/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:11:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/14 16:58:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_change_cursor(t_vm *vm, int index)
{
	if (vm->visu.sdl.current_cursor != index)	
	{
		if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
				|| index == GRAB)
		{
			SDL_SetCursor(vm->visu.sdl.cursor_packers[index].cursor);
			vm->visu.sdl.current_cursor = index;
		}
		vm->visu.event_manager.enable_mouse_up = 0;
	}
}

void		ft_update_cursor(t_vm *vm, t_ixy xy)
{
	if (ft_is_on_buttons(vm, xy, NULL))
		ft_change_cursor(vm, CLICK);
	else if (ft_is_on_draggable(vm, xy, NULL))
		ft_change_cursor(vm, DRAGGABLE);
	else
		ft_change_cursor(vm, REGULAR);
}
