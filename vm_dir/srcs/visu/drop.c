/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:23:51 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_process_drop_dragged_player(t_vm *vm, t_drop_container *dc)
{
	t_player_source	source;

	source = vm->visu.drag_container.drag_union.drag_player.source;
	if (source == SERVER
		&& !vm->visu.drag_container.drag_union.
			drag_player.client_slot->downloaded)
		ft_query_player(vm, vm->visu.drag_container.drag_union.
				drag_player.client_slot);
	if (source == LOCAL || source == DOWNLOADS || source == SERVER)
		ft_copy(vm, dc);
	else
		ft_place_or_swap(vm, dc);
}

void		ft_drop_dragged_player(t_vm *vm, t_ixy mouse)
{
	t_drop_container	dc;
	t_player_source		source;

	if (vm->visu.drag_container.drag_enum == DRAG_PLAYER
		&& vm->visu.drag_container.drag_union.drag_player.player)
	{
		source = vm->visu.drag_container.drag_union.drag_player.source;
		if (ft_is_on_droppable(vm, mouse, &dc))
			ft_process_drop_dragged_player(vm, &dc);
		else if (vm->visu.drag_container.drag_union.drag_player.player
				&& (source == ARENA || source == UPLOAD))
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
