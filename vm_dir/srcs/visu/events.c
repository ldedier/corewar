/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/14 18:51:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_key_down(t_vm *vm, SDL_Keycode code)
{
	(void)vm;
	(void)code;
}

void		ft_key_up(t_vm *vm, SDL_Keycode code)
{
	(void)vm;
	(void)code;
}

int			ft_is_in_rect(t_ixy xy, SDL_Rect rect)
{
	return (xy.x > rect.x && xy.x < rect.x + rect.w &&
				xy.y > rect.y && xy.y < rect.y + rect.h);
}

int			ft_is_on_button(t_ixy xy, t_button *button,
				t_button **to_fill)
{
	if (!button->visible)
		return (0);
	if (ft_is_in_rect(xy, button->rect))
	{
		if (to_fill != NULL)
			*to_fill = button;
		return (1);
	}
	return (0);
}

int			ft_is_on_close(t_vm *vm, t_ixy xy, t_button **but)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_is_on_button(xy, &(vm->visu.positions.arena_slots[i].close), but))
			return (1);
		i++;
	}
	if (ft_is_on_button(xy, &(vm->visu.positions.upload_slot.close), but))
		return (1);
	return (0);
}

int			ft_is_on_buttons(t_vm *vm, t_ixy xy, t_button **but)
{
	int i;

	if (ft_is_on_close(vm, xy, but))
		return (1);
	i = 0;
	while (i < NB_BUTTONS)
	{
		if (ft_is_on_button(xy, &(vm->visu.sdl.buttons[i]), but))
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_relevance(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_printf("player #%d: relevant = %d\n",i, vm->player[i].relevant);
		i++;
	}
}

void		ft_mouse_down(t_vm *vm, SDL_Event event)
{
	t_ixy xy;

	xy = new_ixy(event.button.x, event.button.y);
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		vm->visu.event_manager.enable_mouse_up = 1;
		if (ft_is_on_draggable(vm, xy, &(vm->visu.drag_container)))
		{
			ft_change_cursor(vm, GRAB);
		}
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

	xy = new_ixy( event.button.x, event.button.y);
	ft_drop_dragged_player(vm, xy);
	if (event.button.button == SDL_BUTTON_LEFT &&
		vm->visu.event_manager.enable_mouse_up)
	{
		vm->visu.event_manager.enable_mouse_up = 0;
		ft_process_mouse_up(vm, xy);
	}
	else
		ft_update_cursor(vm, xy);
}

void		ft_mouse_motion(t_vm *vm, SDL_Event event)
{
	t_ixy xy;

	xy = new_ixy(event.motion.x, event.motion.y);
	ft_update_cursor(vm, xy);
	vm->visu.drag_container.x = event.motion.x;
	vm->visu.drag_container.y = event.motion.y;
	ft_is_on_droppable(vm, xy, &(vm->visu.drop_container)); //update droppable player
}

void		ft_process_keys(t_vm *vm, const Uint8 *keys)
{
	(void)vm;
	(void)keys;
}

int			ft_process_events(t_vm *vm)
{
	SDL_Event   event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
				 event.key.keysym.sym == SDLK_ESCAPE))
			vm->visu.active = 0;
		else if (event.type == SDL_KEYDOWN && !event.key.repeat)
			ft_key_down(vm, event.key.keysym.sym);
		else if(event.type == SDL_KEYUP)
			ft_key_up(vm, event.key.keysym.sym);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			ft_mouse_down(vm, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(vm, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(vm, event);
	}
	ft_process_keys(vm, SDL_GetKeyboardState(NULL));
//	ft_process(vm, SDL_GetMouseState(NULL));
//	vm->visu.event_manager.mouse_state = SDL_GetMouseState(NULL, NULL);
	return (0);
}
