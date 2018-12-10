/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 23:37:36 by ldedier          ###   ########.fr       */
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

void		ft_mouse_down(t_vm *vm, SDL_Event event)
{
	(void)vm;
	(void)event;
}

void		ft_mouse_up(t_vm *vm, SDL_Event event)
{
	(void)vm;
	(void)event;
}

void		ft_mouse_motion(t_vm *vm, SDL_Event event)
{
	(void)vm;
	(void)event;
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
	//ft_process(vm, SDL_GetMouseState(NULL));
	return (0);
}
