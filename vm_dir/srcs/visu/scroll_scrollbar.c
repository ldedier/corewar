/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_scrollbar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:10:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 23:39:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_scroll_scrollbar(t_vscrollbar *vscrollbar, double value)
{
	vscrollbar->state = ft_fclamp(0,
			vscrollbar->state - value *
			(double)vscrollbar->height / (double)vscrollbar->compressed_height,
			1);
}

void	ft_scroll_up(t_vm *vm, t_button *button)
{
	(void)vm;
	ft_scroll_scrollbar(button->button_union.vscrollbar, 0.03);
}

void	ft_scroll_down(t_vm *vm, t_button *button)
{
	(void)vm;
	ft_scroll_scrollbar(button->button_union.vscrollbar, -0.03);
}

void	ft_wheel_event(t_vm *vm, SDL_Event event)
{
	int		i;
	t_ixy	xy;

	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_is_in_scrollbar_focus(vm->visu.players_list[i].vscrollbar))
		{
			ft_scroll_scrollbar(&vm->visu.players_list[i].vscrollbar,
				event.wheel.y * 0.03);
			SDL_GetMouseState(&(xy.x), &(xy.y));
			ft_update_cursor(vm, xy);
			return ;
		}
		i++;
	}
}
