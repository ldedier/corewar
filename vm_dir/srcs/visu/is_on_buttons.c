/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_buttons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:54:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 18:39:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		ft_is_in_scrolled_rect(t_ixy xy, SDL_Rect rect,
		t_vscrollbar vscrollbar)
{
	if (xy.y > vscrollbar.pos.y
			&& xy.y < vscrollbar.pos.y + vscrollbar.height)
	{
		xy.y += ft_get_scrolled_height(vscrollbar);
		return (ft_is_in_rect(xy, rect));
	}
	return (0);
}

int				ft_is_on_button(t_vm *vm, t_ixy xy, t_button *button,
		t_button **to_fill)
{
	if (!button->visible || !button->enabled
			|| (((button->phase != vm->visu.phase)
			|| vm->visu.notification.image_index != -1)
				&& button != &vm->visu.buttons[OK_BUTTON]))
		return (0);
	if (button->vscrollbar == NULL
			|| !ft_to_print_scrollbar(*button->vscrollbar))
	{
		if (ft_is_in_rect(xy, button->rect))
		{
			if (to_fill != NULL)
				*to_fill = button;
			return (1);
		}
	}
	else if (button->vscrollbar)
	{
		if (ft_is_in_scrolled_rect(xy, button->rect, *button->vscrollbar))
		{
			if (to_fill != NULL)
				*to_fill = button;
			return (1);
		}
	}
	return (0);
}

int				ft_is_on_close(t_vm *vm, t_ixy xy, t_button **but)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (ft_is_on_button(vm, xy, &(vm->visu.positions.arena_slots[i].close),
			but))
			return (1);
	}
	if (ft_is_on_button(vm, xy, &(vm->visu.positions.upload_slot.close), but))
		return (1);
	i = -1;
	while (++i < NB_SOURCES)
	{
		if (ft_to_print_scrollbar(vm->visu.players_list[i].vscrollbar))
		{
			if (ft_is_on_button(vm, xy, &(vm->visu.players_list[i].
				vscrollbar.up_button), but))
				return (1);
			if (ft_is_on_button(vm, xy, &(vm->visu.players_list[i].
				vscrollbar.down_button), but))
				return (1);
		}
	}
	return (0);
}

int				ft_is_on_buttons(t_vm *vm, t_ixy xy, t_button **but)
{
	int		i;
	t_list	*ptr;

	if (ft_is_on_close(vm, xy, but))
		return (1);
	i = -1;
	while (++i < NB_BUTTONS)
	{
		if (ft_is_on_button(vm, xy, &(vm->visu.buttons[i]), but)
				&& (vm->client.active || i >= FIGHT_BUTTON))
			return (1);
	}
	if (vm->client.active)
	{
		ptr = vm->client.client_slots;
		while (ptr != NULL)
		{
			if (ft_is_on_button(vm, xy,
				&((t_client_slot *)(ptr->content))->download,
					but))
				return (1);
			ptr = ptr->next;
		}
	}
	return (0);
}
