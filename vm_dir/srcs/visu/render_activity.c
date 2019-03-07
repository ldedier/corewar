/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_activity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:57:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 16:13:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_mark_as_instruction(t_vm *vm, SDL_Rect rect, t_process *process)
{
	int color;

	color = (process->player->color.value);
	ft_draw_rect_surface(vm->visu.sdl.w_surface, rect, color);
	return (0);
}

static int	ft_render_process_instruction(t_vm *vm, t_process *process)
{
	int			i;
	SDL_Rect	rect;

	i = 1;
	rect = get_rect_from_pc(vm, process->pc);
	if (ft_mark_as_instruction(vm, rect, process))
		return (1);
	while (i < process->ins_bytelen)
	{
		rect = get_rect_from_pc(vm, process->pc + i);
		if (ft_mark_as_instruction(vm, rect, process))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_render_process(t_vm *vm, t_process *process)
{
	SDL_Rect		rect;
	t_color_manager	c;
	int				index;

	index = process->player->color.index;
	vm->metarena[process->pc].process_color_index = index;
	c = ft_get_color(process->player->color.value);
	rect = get_rect_from_pc(vm, process->pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, c.color);
	if (ft_render_process_instruction(vm, process))
		return (1);
	if (process->carry)
	{
		rect.x++;
		rect.y++;
		rect.w -= 2;
		rect.h -= 2;
		ft_draw_rect_surface(vm->visu.sdl.w_surface, rect, 0xffffff);
	}
	return (0);
}

int			ft_render_all_process(t_vm *vm)
{
	t_list		*ptr;
	t_process	*process;

	ptr = vm->proc;
	while (ptr != NULL)
	{
		process = (t_process *)(ptr->content);
		ft_render_process(vm, process);
		ptr = ptr->next;
	}
	return (0);
}
