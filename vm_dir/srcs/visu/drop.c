/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/14 19:04:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_droppable(t_vm *vm, t_ixy mouse, t_xy xy)
{
	return (ft_fabs((mouse.x - vm->visu.drag_container.diff_x) -
				xy.x) < (vm->visu.center.player_w) && 
					ft_fabs((mouse.y - vm->visu.drag_container.diff_y) -
						xy.y) < (vm->visu.center.player_padding - 1));
}

int		ft_is_on_droppable(t_vm *vm, t_ixy mouse, t_drop_container *dc)
{
	int i;

	if (vm->visu.drag_container.player != NULL)
	{
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (ft_is_droppable(vm, mouse,
				vm->visu.positions.arena_slots[i].player))
			{
				dc->player = &(vm->player[i]);
				dc->close = &(vm->visu.positions.arena_slots[i].close);
				return (1);
			}
			i++;
		}
		if (ft_is_droppable(vm, mouse, vm->visu.positions.upload_slot.player))
		{
			dc->player = &(vm->client.upload_player);
			dc->close = &(vm->visu.positions.upload_slot.close);
			return (1);
		}
	}
	dc->player = NULL;
	return (0);
}

void	ft_drop_dragged_player(t_vm *vm, t_ixy mouse)
{
	t_drop_container	dc;
	t_player			tmp;

	if (ft_is_on_droppable(vm, mouse, &dc))
	{
		if (vm->visu.drag_container.source != LOCAL)
		{
			tmp = (*dc.player);
			*(dc.player) = *(vm->visu.drag_container.player);
			if (tmp.relevant)
			{
				*(vm->visu.drag_container.player) = tmp;
				vm->visu.drag_container.close->visible = 1;
			}
			else
			{
				vm->visu.drag_container.player->relevant = 0;
				vm->visu.drag_container.close->visible = 0;
				dc.close->visible = 1;
			}
		}
		else
		{
			*(dc.player) = *(vm->visu.drag_container.player);
			dc.close->visible = 1;
		}
		dispatch_players(vm);
	}
	else if (vm->visu.drag_container.player)
		vm->visu.drag_container.close->visible = 1;
	vm->visu.drag_container.player = NULL;
	vm->visu.drop_container.player = NULL;
}
