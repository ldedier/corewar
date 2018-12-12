/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/12 22:11:57 by ldedier          ###   ########.fr       */
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

int			ft_get_arena_close_id(t_vm *vm, int x, int y)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant &&
				vm->visu.positions.arena_slots[i].close.x + CROSS_IB < x &&
				vm->visu.positions.arena_slots[i].close.x + CROSS_BORDER > x &&
				vm->visu.positions.arena_slots[i].close.y < y &&
				vm->visu.positions.arena_slots[i].close.y + CROSS_BORDER -
					CROSS_IB > y
			)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_is_on_clickable(t_vm *vm, int x, int y)
{
	if (ft_get_arena_close_id(vm, x, y) != -1)
		return (1);
	return (0);
}

int		ft_is_on_player(t_vm *vm, int x, int y, t_xy player_xy)
{
	return ((ft_get_arena_close_id(vm, x, y) == -1) &&
			player_xy.x < x &&
			player_xy.x + vm->visu.center.player_w > x &&
			player_xy.y < y &&
			player_xy.y + vm->visu.center.player_h  > y);
}

void	ft_fill_drag_container(t_drag_container *dc, int x, int y)
{
	if (dc != NULL)
	{
		dc->x = x;
		dc->y = y;
	}
}

void	ft_populate_drag_container(t_drag_container *dc, t_player *player,
			t_xy player_xy, int from_arena)
{
	if (dc != NULL)
	{
		dc->from_arena = from_arena;
		dc->player = player;
		dc->diff_x = dc->x - player_xy.x;
		dc->diff_y = dc->y - player_xy.y;
	}
}

int		ft_is_on_draggable(t_vm *vm, int x, int y, t_drag_container *dc)
{
	int i;

	i = 0;
	ft_fill_drag_container(dc, x, y);
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant &&
				ft_is_on_player(vm, x, y,
					vm->visu.positions.arena_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->player[i]),
				vm->visu.positions.arena_slots[i].player, 1);
			return (1);
		}
		if (vm->local_player[i].relevant &&
				ft_is_on_player(vm, x, y,
					vm->visu.positions.local_slots[i].player))
		{
			ft_populate_drag_container(dc, &(vm->local_player[i]),
				vm->visu.positions.local_slots[i].player, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

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

void		ft_update_cursor(t_vm *vm, int x, int y)
{
	if (ft_is_on_clickable(vm, x, y))
		ft_change_cursor(vm, CLICK);
	else if (ft_is_on_draggable(vm, x, y, NULL))
		ft_change_cursor(vm, DRAGGABLE);
	else
		ft_change_cursor(vm, REGULAR);
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
	int id;

	if ((id = ft_get_arena_close_id(vm, x, y)) != -1)
	{
		vm->player[id].relevant = 0;
		dispatch_players(vm);
		ft_update_cursor(vm, x, y);
	}
}

void		ft_drop_dragged_player(t_vm *vm, int x, int y)
{
	int			i;
	t_player	tmp;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_fabs((x - vm->visu.drag_container.diff_x) -
			vm->visu.positions.arena_slots[i].player.x) < DROP_TOLERANCE && 
			ft_fabs((y - vm->visu.drag_container.diff_y) -
				vm->visu.positions.arena_slots[i].player.y) < DROP_TOLERANCE)
		{
			if (vm->visu.drag_container.from_arena)
			{
				tmp = vm->player[i];
				vm->player[i] = *(vm->visu.drag_container.player);
				*(vm->visu.drag_container.player) = tmp;
			}
			else
				vm->player[i] = *(vm->visu.drag_container.player);
			dispatch_players(vm);
			break;
		}
		i++;
	}
}

void		ft_mouse_up(t_vm *vm, SDL_Event event)
{
	if (vm->visu.drag_container.player != NULL)
		ft_drop_dragged_player(vm, event.button.x, event.button.y);
	vm->visu.drag_container.player = NULL;
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
