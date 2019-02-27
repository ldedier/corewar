/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/27 14:42:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_process_drop_dragged_player(t_vm *vm, t_drop_container *dc)
{
	if (vm->visu.drag_container.drag_union.drag_player.source ==
			SERVER && !vm->visu.drag_container.drag_union.
			drag_player.client_slot->downloaded)
		ft_query_player(vm, vm->visu.drag_container.drag_union.
				drag_player.client_slot);
	if (vm->visu.drag_container.drag_union.drag_player.source
			== LOCAL || vm->visu.drag_container.drag_union.
			drag_player.source == DOWNLOADS || vm->visu.
			drag_container.drag_union.
			drag_player.source == SERVER)
		ft_copy(vm, dc);
	else
		ft_place_or_swap(vm, dc);
}

void	ft_drop_dragged_player(t_vm *vm, t_ixy mouse)
{
	t_drop_container	dc;

	if (vm->visu.drag_container.drag_enum == DRAG_PLAYER &&
			vm->visu.drag_container.drag_union.drag_player.player)
	{
		if (ft_is_on_droppable(vm, mouse, &dc))
			ft_process_drop_dragged_player(vm, &dc);
		else if (vm->visu.drag_container.drag_union.drag_player.player &&
				(vm->visu.drag_container.drag_union.drag_player.source
				== ARENA || vm->visu.drag_container.drag_union.
				drag_player.source == UPLOAD))
		{
			vm->visu.drag_container.drag_union.drag_player.player->relevant = 0;
			set_color_sdl(vm, vm->visu.drag_container.drag_union.
				drag_player.player);
			dispatch_players(vm, NULL);
		}
	}
	if (vm->client.upload_player.relevant)
		vm->visu.buttons[UPLOAD_BUTTON].enabled = 1;
	vm->visu.drag_container.drag_union.drag_player.player = NULL;
	vm->visu.drag_container.drag_union.vscrollbar = NULL;
	vm->visu.drop_container.player = NULL;
}
