/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:46:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:17:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_render_live(t_fade *fade, t_vm *vm)
{
	SDL_Rect		rect;
	t_color_manager	cm;

	cm = ft_interpolate_color(fade->color, BACKGROUND_COL,
			fade->value / (double)MAX_FADE);
	rect = get_rect_from_pc(vm, fade->pc);
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, fade->color);
	if (!--fade->value)
		return (1);
	return (0);
}

void		ft_render_lives_at_head(t_list **temp, t_list **prev,
		t_list **start, t_vm *vm)
{
	while (*temp != NULL && ft_render_live((t_fade *)((*temp)->content), vm))
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

void		ft_render_lives_at_body(t_list **temp, t_list **prev, t_vm *vm)
{
	while (*temp != NULL)
	{
		while (*temp != NULL &&
			!ft_render_live((t_fade *)((*temp)->content), vm))
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

int			ft_render_all_lives(t_vm *vm)
{
	t_list		*ptr;
	t_list		*prev;

	prev = NULL;
	ptr = vm->live_ok;
	ft_render_lives_at_head(&ptr, &prev, &vm->live_ok, vm);
	ft_render_lives_at_body(&ptr, &prev, vm);
	return (0);
}
