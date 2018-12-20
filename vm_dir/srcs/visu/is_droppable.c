/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_droppable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:30:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 20:31:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_droppable(t_vm *vm, t_ixy mouse, t_xy xy)
{
	return (ft_fabs((mouse.x - vm->visu.drag_container.diff_x) -
				xy.x) < (vm->visu.center.player_w) && 
					ft_fabs((mouse.y - vm->visu.drag_container.diff_y) -
						xy.y) < (ft_max(vm->visu.center.player_padding,
								vm->visu.center.player_h)));
}

int		ft_is_droppable_scrollbar(t_vm *vm, t_ixy mouse, t_xy xy,
			t_vscrollbar vscrollbar)
{
	int		scrolled_height;

	scrolled_height = ft_get_scrolled_height(vscrollbar);
	if (!ft_to_print_scrollbar(vscrollbar))
		return (ft_is_droppable(vm, mouse, xy));
	if (xy.y - scrolled_height + vm->visu.center.player_h > vscrollbar.pos.y &&
			xy.y - scrolled_height < vscrollbar.pos.y + vscrollbar.height)
	{
		mouse.y += scrolled_height;
		return (ft_is_droppable(vm, mouse, xy));
	}
	return (0);
}

int		ft_is_on_upload_slot_drop(t_vm *vm, t_ixy mouse, t_drop_container *dc)
{
	if (vm->visu.drag_container.drag_union.drag_player.source != SERVER &&
			ft_is_droppable_scrollbar(vm, mouse, vm->visu.positions.upload_slot.player,
				vm->visu.players_list[UPLOAD].vscrollbar))
	{
		dc->player = &(vm->client.upload_player);
		dc->close = &(vm->visu.positions.upload_slot.close);
		return (1);
	}
	return (0);
}

int		ft_is_on_droppable(t_vm *vm, t_ixy mouse, t_drop_container *dc)
{
	int i;

	if (vm->visu.drag_container.drag_union.drag_player.player != NULL)
	{
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (ft_is_droppable_scrollbar(vm, mouse,
				vm->visu.positions.arena_slots[i].player,
					vm->visu.players_list[ARENA].vscrollbar))
			{
				dc->player = &(vm->player[i]);
				dc->close = &(vm->visu.positions.arena_slots[i].close);
				return (1);
			}
			i++;
		}
		if (ft_is_on_upload_slot_drop(vm, mouse, dc))
			return (1);
	}
	dc->player = NULL;
	return (0);
}
