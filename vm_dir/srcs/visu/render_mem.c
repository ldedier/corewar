/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:08:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/20 22:20:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

SDL_Rect get_rect_from_pc(t_vm *vm, int pc)
{
	SDL_Rect	res;
	int			x;
	int			y;

	x = pc % MEM_COLS;
	y = pc / MEM_COLS;
	res.w = vm->visu.center.glyph_width * 2 + vm->visu.center.x_diff_byte + 
		vm->visu.center.x_diff;
	res.h = vm->visu.center.glyph_height + vm->visu.center.y_diff;
	res.x = vm->visu.center.left_margin + x * (vm->visu.center.glyph_width * 2
			+ vm->visu.center.x_diff_byte + vm->visu.center.x_diff) -
		vm->visu.center.x_diff / 2;
	res.y = vm->visu.center.top_margin + y * (vm->visu.center.glyph_height +
			vm->visu.center.y_diff) - vm->visu.center.y_diff / 2;
	return (res);
}

int		ft_render_process(t_vm *vm, t_process *process)
{
	SDL_Rect rect;
	t_color_manager c;

	vm->metarena[process->pc].process_color_index = process->player->color.index;
	c = ft_get_color(*(int *)(process->player->color.value));
	rect = get_rect_from_pc(vm, process->pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, c.color);
	return (0);
}

int		ft_render_all_process(t_vm *vm)
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

int		ft_print_byte_composant(t_vm *vm, t_xy *dist, t_metadata meta, int byte)
{
	int			ascii_byte;
	SDL_Rect	rect;
	int			color_index;

	rect.w = vm->visu.center.glyph_width;
	rect.h = vm->visu.center.glyph_height;
	rect.x = dist->x;
	rect.y = dist->y;
	if (byte < 10)
		ascii_byte = byte + '0';
	else
		ascii_byte = byte + 'a' - 10;
	if (meta.process_color_index)
		color_index = 0;
	else
		color_index = meta.color_index;
	if (SDL_BlitScaled(
				vm->visu.sdl.atlas[color_index][ascii_byte].surface, NULL,
				vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	dist->x += vm->visu.center.glyph_width;
	return (0);
}

int		ft_print_byte(t_vm *vm, int byte, t_metadata meta, t_xy *dist)
{
	if (ft_print_byte_composant(vm, dist, meta, (byte / 16) % 16))
		return (1);
	dist->x += vm->visu.center.x_diff_byte;
	if (ft_print_byte_composant(vm, dist, meta, byte % 16))
		return (1);
	return (0);
}

int		ft_render_memory(t_vm *vm)
{
	int			i;
	int			j;
	t_xy		dist;

	i = 0;
	dist.y = vm->visu.center.top_margin;
	while (i * MEM_COLS < MEM_SIZE)
	{
		j = 0;
		dist.x = vm->visu.center.left_margin;
		while (j < MEM_COLS)
		{
			if (i * MEM_COLS + j < MEM_SIZE)
			{
				if (ft_print_byte(vm,(unsigned char)vm->arena[i * MEM_COLS + j],
						vm->metarena[i * MEM_COLS + j], &dist))
					return (1);
				dist.x += vm->visu.center.x_diff;
			}
			j++;
		}
		dist.y += vm->visu.center.glyph_height + vm->visu.center.y_diff;
		i++;
	}
	return (0);
}
