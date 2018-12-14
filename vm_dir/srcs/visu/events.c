/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 19:12:42 by ldedier          ###   ########.fr       */
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

int			ft_is_in_rect(int x, int y, SDL_Rect rect)
{
	return (x > rect.x && x < rect.x + rect.w &&
				y > rect.y && y < rect.y + rect.h);
}

int			ft_is_on_button(t_vm *vm, int x, int y, t_button **button)
{
	int i;

	i = 0;
	while (i < NB_BUTTONS)
	{
		if (ft_is_in_rect(x, y,vm->visu.sdl.buttons[i].rect))
		{
			if (button != NULL)
				*button = &(vm->visu.sdl.buttons[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_is_on_clickable(t_vm *vm, int x, int y, t_clickable_container *cc)
{
	if (ft_is_on_close(vm, x, y, (cc == NULL ? NULL : (t_player **)&(cc->clickable))))
	{
		if (cc != NULL)
			cc->clickable_nature = PLAYER_CROSS;
		return (1);
	}
	if (ft_is_on_button(vm, x, y, cc == NULL ? NULL : (t_button**)&(cc->clickable)))
	{
		if (cc != NULL)
			cc->clickable_nature = BUTTON;
		return (1);
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
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		vm->visu.event_manager.enable_mouse_up = 1;
		if (ft_is_on_draggable(vm, event.button.x, event.button.y,
				&(vm->visu.drag_container)))
		{
			ft_change_cursor(vm, GRAB);
		}
	}
}

void		ft_process_mouse_up(t_vm *vm, int x, int y)
{
	t_clickable_container	cc;

	if ((ft_is_on_clickable(vm, x, y, &cc)))
	{
		if (cc.clickable_nature == PLAYER_CROSS)
		{
			((t_player *)(cc.clickable))->relevant = 0;
			dispatch_players(vm);
			ft_update_cursor(vm, x, y);

		}
		else if (cc.clickable_nature == BUTTON)
		{
			((t_button *)(cc.clickable))->action(vm, cc.button_union);
		}
	}
}

void		ft_mouse_up(t_vm *vm, SDL_Event event)
{
	ft_drop_dragged_player(vm, event.button.x, event.button.y);
	if (event.button.button == SDL_BUTTON_LEFT &&
		vm->visu.event_manager.enable_mouse_up)
	{
		vm->visu.event_manager.enable_mouse_up = 0;
		// process_buttons/drag
		ft_process_mouse_up(vm, event.button.x, event.button.y);
	}
	else
		ft_update_cursor(vm, event.button.x, event.button.y);
}

void		ft_mouse_motion(t_vm *vm, SDL_Event event)
{
	ft_update_cursor(vm, event.motion.x, event.motion.y);
	vm->visu.drag_container.x = event.motion.x;
	vm->visu.drag_container.y = event.motion.y;
	ft_is_on_droppable(vm, event.motion.x, event.motion.y,
		&(vm->visu.drop_container.player));
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
