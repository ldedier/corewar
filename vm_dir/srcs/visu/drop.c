/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/18 22:52:35 by ldedier          ###   ########.fr       */
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
		if (vm->visu.drag_container.drag_union.drag_player.source != SERVER &&
			ft_is_droppable_scrollbar(vm, mouse, vm->visu.positions.upload_slot.player,
				vm->visu.players_list[UPLOAD].vscrollbar))
		{
			dc->player = &(vm->client.upload_player);
			dc->close = &(vm->visu.positions.upload_slot.close);
			return (1);
		}
	}
	dc->player = NULL;
	return (0);
}

void	ft_remove_color_player(t_vm *vm, t_player *player)
{
	player->relevant = 0;
	set_color(player, vm->color);
	player->relevant = 1;
}

void	ft_swap(t_vm *vm, t_drop_container *dc, t_player dragged_on_player)
{
	*(vm->visu.drag_container.drag_union.drag_player.player) = dragged_on_player;
	if (vm->visu.drag_container.drag_union.drag_player.close)
		vm->visu.drag_container.drag_union.drag_player.close->visible = 1;
	if (dc->player == &vm->client.upload_player) //on drop dans upload
		ft_remove_color_player(vm, dc->player);
	if (vm->visu.drag_container.drag_union.drag_player.source == UPLOAD) //on drop depuis upload
		ft_remove_color_player(vm, vm->visu.drag_container.drag_union.drag_player.player);
}

void	ft_place(t_vm *vm, t_drop_container *dc)
{
	if (dc->player == &vm->client.upload_player) //on place dans upload
		ft_remove_color_player(vm, dc->player);
	vm->visu.drag_container.drag_union.drag_player.player->relevant = 0;
	vm->visu.drag_container.drag_union.drag_player.player->color.value = NULL;
	if (vm->visu.drag_container.drag_union.drag_player.close)
		vm->visu.drag_container.drag_union.drag_player.close->visible = 0;
	dc->close->visible = 1;
}

void	ft_place_or_swap(t_vm *vm, t_drop_container *dc)
{
	t_player	tmp;

	tmp = *dc->player;
	*dc->player = *(vm->visu.drag_container.drag_union.drag_player.player);
	if (tmp.relevant)
		ft_swap(vm, dc, tmp);
	else
		ft_place(vm, dc);
}

void	ft_copy(t_vm *vm, t_drop_container *dc)
{
	if (dc->player == &vm->client.upload_player) //usefull si copie from arena
		dc->player->color.value = NULL;
	dc->player->relevant = 0;
	set_color(dc->player, vm->color);
	*(dc->player) = *(vm->visu.drag_container.drag_union.drag_player.player);
	dc->close->visible = 1;
}

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
	vm->visu.drag_container.drag_union.drag_player.player = NULL;
	vm->visu.drag_container.drag_union.vscrollbar = NULL;
	vm->visu.drop_container.player = NULL;
}
