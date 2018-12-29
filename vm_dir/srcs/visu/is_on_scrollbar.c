/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_scrollbar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:18:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/21 14:08:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_on_scrollbar_bar(t_ixy xy, t_vscrollbar  vscrollbar)
{
	t_ixy scrollbar_bar_height_y;

	if (!ft_to_print_scrollbar(vscrollbar))
		return (0);
	scrollbar_bar_height_y = ft_get_vscrollbar_bar_height_y(vscrollbar);
	return (xy.x > vscrollbar.pos.x &&
			xy.x < vscrollbar.pos.x + vscrollbar.bar_width &&
			xy.y > scrollbar_bar_height_y.y &&
			xy.y < scrollbar_bar_height_y.y + scrollbar_bar_height_y.x
			);
}

int		ft_is_on_scrollbars(t_vm *vm, t_ixy xy, t_drag_container *dc)
{
	int i;

	if (vm->visu.phase == PHASE_INIT)
	{
		i = 0;
		while (i < NB_SOURCES)
		{
			if (ft_is_on_scrollbar_bar(xy, vm->visu.players_list[i].vscrollbar))
			{
				ft_populate_drag_container_vscrollbar(dc, 
						&vm->visu.players_list[i].vscrollbar);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
