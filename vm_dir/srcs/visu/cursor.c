/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:11:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 21:20:33 by ldedier          ###   ########.fr       */
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

int		ft_populate_cursor(t_cursor_packer *cp, char *str, int hot_x, int hot_y)
{
	if (!(cp->surface = ft_load_image(str)))
		return (1);
	if (!(cp->cursor = SDL_CreateColorCursor(cp->surface, hot_x, hot_y)))
		return (1);
	return (0);
}

int		ft_init_cursors(t_visu *v)
{
	if (ft_populate_cursor(&(v->sdl.cursor_packers[GRAB]),
				PATH"/resources/grab.png", 7, 3))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[DRAGGABLE]),
				PATH"/resources/draggable.png", 7, 5))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[CLICK]),
				PATH"/resources/click.png", 5, 0))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[REGULAR]),
				PATH"/resources/regular.png", 0, 0))
		return (1);
	return (0);
}
