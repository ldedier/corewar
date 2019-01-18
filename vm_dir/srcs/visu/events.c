/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 15:25:47 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_key_down(t_vm *vm, SDL_Keycode code)
{
	if (code == SDLK_SPACE)
	{
		if (vm->visu.phase == PHASE_INIT)
			start_fight(vm);
		else
			vm->visu.time_manager.pause = !vm->visu.time_manager.pause;
	}
	else if (code == SDLK_RIGHT && vm->visu.time_manager.pause)
		process_cycle_all(vm);
	else if (code == SDLK_r)
		display_registers(vm);
}

void		ft_key_up(t_vm *vm, SDL_Keycode code)
{
	(void)vm;
	(void)code;
}

	
void	ft_increment_cpt(t_vm *vm, int direction)
{
	if (vm->visu.time_manager.cycles_per_turn <= 4)
		vm->visu.time_manager.cycles_per_turn =
		ft_fmax(vm->visu.time_manager.cycles_per_turn +
				(direction / 10.0), 0.0166);
	else if (vm->visu.time_manager.cycles_per_turn >= 5000)
		vm->visu.time_manager.cycles_per_turn = ft_fmin(20000, 
			vm->visu.time_manager.cycles_per_turn + direction * 1000);
	else if(vm->visu.time_manager.cycles_per_turn >= 500)
		vm->visu.time_manager.cycles_per_turn += direction * 100;
	else
		vm->visu.time_manager.cycles_per_turn += direction;
}

void		ft_process_keys(t_vm *vm, const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_UP])
	{
		ft_increment_cpt(vm, 1);
	}
	if(keys[SDL_SCANCODE_DOWN])
		ft_increment_cpt(vm, -1);
//	if (keys[SDLK_KP_6] && vm->visu.time_manager.pause)
//		process_cycle_all(vm);
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
		else if (event.type == SDL_MOUSEWHEEL)
			ft_wheel_event(vm, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(vm, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(vm, event);
	}
	ft_process_button_pressed(vm);
	if (vm->visu.phase == PHASE_PLAY)
	ft_process_keys(vm, SDL_GetKeyboardState(NULL));
//	ft_process(vm, SDL_GetMouseState(NULL));
//	vm->visu.event_manager.mouse_state = SDL_GetMouseState(NULL, NULL);
	return (0);
}
