/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 22:03:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_drop_dragged_player(t_vm *vm, t_ixy mouse)
{
	t_drop_container	dc;

	if (vm->visu.drag_container.drag_enum == DRAG_PLAYER &&
			vm->visu.drag_container.drag_union.drag_player.player)
	{
		if (ft_is_on_droppable(vm, mouse, &dc))
		{
			if (vm->visu.drag_container.drag_union.drag_player.source == LOCAL ||
				vm->visu.drag_container.drag_union.drag_player.source == SERVER)
				ft_copy(vm, &dc);
			else
				ft_place_or_swap(vm, &dc);
			dispatch_players(vm);
		}
		else if (vm->visu.drag_container.drag_union.drag_player.player &&
				(vm->visu.drag_container.drag_union.drag_player.source
				== ARENA || vm->visu.drag_container.drag_union.
				drag_player.source == UPLOAD))
		{
			vm->visu.drag_container.drag_union.drag_player.player->relevant = 0;
			set_color(vm->visu.drag_container.drag_union.drag_player.player, vm->color);
			dispatch_players(vm);
		}
	}
	vm->visu.drag_container.drag_union.drag_player.player = NULL; //ptet ca
	vm->visu.drag_container.drag_union.vscrollbar = NULL; //ptet ca
	vm->visu.drop_container.player = NULL;
}
