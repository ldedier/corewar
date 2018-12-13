/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 19:09:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_droppable(t_vm *vm, int x, int y, t_xy xy)
{
	return (ft_fabs((x - vm->visu.drag_container.diff_x) -
				xy.x) < (vm->visu.center.player_w) && 
					ft_fabs((y - vm->visu.drag_container.diff_y) -
						xy.y) < (vm->visu.center.player_padding - 1));
}

int		ft_is_on_droppable(t_vm *vm, int x, int y, t_player **to_drop_on)
{
	int i;

	if (vm->visu.drag_container.player != NULL)
	{
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (ft_is_droppable(vm, x, y,
				vm->visu.positions.arena_slots[i].player))
			{
				*to_drop_on = &(vm->player[i]);
				return (1);
			}
			i++;
		}
		if (ft_is_droppable(vm, x, y, vm->visu.positions.upload_slot.player))
		{
			*to_drop_on = &(vm->client.upload_player);
			return (1);
		}
	}
	*to_drop_on = NULL;
	return (0);
}

void	ft_drop_dragged_player(t_vm *vm, int x, int y)
{
	t_player	*to_drop_on;
	t_player	tmp;

	if (ft_is_on_droppable(vm, x, y, &to_drop_on))
	{
		if (vm->visu.drag_container.source != LOCAL)
		{
			tmp = *to_drop_on;
			*to_drop_on = *(vm->visu.drag_container.player);
			if (tmp.relevant)
				*(vm->visu.drag_container.player) = tmp;
			else
				vm->visu.drag_container.player->relevant = 0;
		}
		else
			*to_drop_on = *(vm->visu.drag_container.player);
		dispatch_players(vm);
	}
	vm->visu.drag_container.player = NULL;
	vm->visu.drop_container.player = NULL;
}
