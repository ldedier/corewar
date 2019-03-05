/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:47:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:12:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		ft_render_fade(t_fade *fade, t_vm *vm)
{
	SDL_Rect		rect;
	t_color_manager	cm;

	cm = ft_interpolate_color(fade->color, BACKGROUND_COL,
			fade->value / (double)MAX_FADE);
	rect = get_rect_from_pc(vm, fade->pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, cm.color);
	if (!--fade->value)
		return (1);
	return (0);
}

static void		ft_render_fades_at_head(t_list **temp, t_list **prev,
					t_list **start, t_vm *vm)
{
	while (*temp != NULL && ft_render_fade((t_fade *)((*temp)->content), vm))
	{
		*start = (*temp)->next;
		free((*temp)->content);
		free(*temp);
		*temp = *start;
	}
	if (*temp != NULL)
	{
		*prev = *temp;
		*temp = (*temp)->next;
	}
}

static void		ft_render_fades_at_body(t_list **temp, t_list **prev, t_vm *vm)
{
	while (*temp != NULL)
	{
		while (*temp != NULL &&
			!ft_render_fade((t_fade *)((*temp)->content), vm))
		{
			*prev = *temp;
			*temp = (*temp)->next;
		}
		if (*temp != NULL)
		{
			(*prev)->next = (*temp)->next;
			free((*temp)->content);
			free(*temp);
			*temp = (*prev)->next;
		}
	}
}

int				ft_render_all_dead_process(t_vm *vm)
{
	t_list		*ptr;
	t_list		*prev;

	prev = NULL;
	ptr = vm->killed_proc;
	ft_render_fades_at_head(&ptr, &prev, &vm->killed_proc, vm);
	ft_render_fades_at_body(&ptr, &prev, vm);
	return (0);
}
