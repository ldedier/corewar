/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:58:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/04 03:14:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_mouse_down(t_vm *vm, SDL_Event event)
{
	t_ixy			xy;
	t_vscrollbar	*vscrollbar;

	xy = new_ixy(event.button.x, event.button.y);
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		ft_is_on_buttons(vm, xy, &vm->visu.event_manager.pressed_button);
		vm->visu.event_manager.enable_mouse_up = 1;
		if (ft_is_on_draggable(vm, xy, &(vm->visu.drag_container)))
		{
			ft_change_cursor(vm, GRAB);
		}
		else if (get_vscrollbar(vm, xy, &vscrollbar))
			ft_swing_scrollbar(vscrollbar, xy);
		ft_is_on_droppable(vm, xy, &(vm->visu.drop_container)); //update droppable player
	}
}

void		ft_process_mouse_up(t_vm *vm, t_ixy xy)
{
	t_button	*button;

	if ((ft_is_on_buttons(vm, xy, &button)))
		button->on_click(vm, button, xy);
}

void		ft_mouse_up(t_vm *vm, SDL_Event event)
{
	t_ixy xy;

	vm->visu.event_manager.pressed_button = NULL;
	xy = new_ixy( event.button.x, event.button.y);
	ft_drop_dragged_player(vm, xy);
	if (event.button.button == SDL_BUTTON_LEFT &&
		vm->visu.event_manager.enable_mouse_up)
	{
		vm->visu.event_manager.enable_mouse_up = 0;
		ft_process_mouse_up(vm, xy);
	}
	ft_update_cursor(vm, xy);
}

void		ft_mouse_motion(t_vm *vm, SDL_Event event)
{
	t_ixy xy;

	xy = new_ixy(event.motion.x, event.motion.y);
	ft_update_cursor(vm, xy);
	vm->visu.drag_container.x = event.motion.x;
	vm->visu.drag_container.y = event.motion.y;
	if (vm->visu.drag_container.drag_enum == DRAG_VSCROLLBAR &&
			vm->visu.drag_container.drag_union.vscrollbar)
		ft_update_scrollbar(vm, vm->visu.drag_container.drag_union.vscrollbar);
	ft_is_on_droppable(vm, xy, &(vm->visu.drop_container)); //update droppable container
}

int			ft_process_button_pressed(t_vm *vm)
{
	if (vm->visu.event_manager.pressed_button)
		vm->visu.event_manager.pressed_button->on_press(vm,
			vm->visu.event_manager.pressed_button);
	return (0);
}
