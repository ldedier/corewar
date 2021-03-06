/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:26:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_remove_color_player(t_vm *vm, t_player *player)
{
	player->relevant = 0;
	set_color_sdl(vm, player);
	player->relevant = 1;
}

static void	ft_swap(t_vm *vm, t_drop_container *dc, t_player dragged_player)
{
	*(vm->visu.drag_container.drag_union.drag_player.player) = dragged_player;
	if (vm->visu.drag_container.drag_union.drag_player.close)
		vm->visu.drag_container.drag_union.drag_player.close->visible = 1;
	if (dc->player == &vm->client.upload_player)
		ft_remove_color_player(vm, dc->player);
	if (vm->visu.drag_container.drag_union.drag_player.source == UPLOAD)
		ft_remove_color_player(vm, vm->visu.drag_container.
				drag_union.drag_player.player);
}

static void	ft_place(t_vm *vm, t_drop_container *dc)
{
	if (dc->player == &vm->client.upload_player)
		ft_remove_color_player(vm, dc->player);
	vm->visu.drag_container.drag_union.drag_player.player->relevant = 0;
	vm->visu.drag_container.drag_union.drag_player.player->color.value = 1;
	if (vm->visu.drag_container.drag_union.drag_player.close)
		vm->visu.drag_container.drag_union.drag_player.close->visible = 0;
	dc->close->visible = 1;
}

void		ft_place_or_swap(t_vm *vm, t_drop_container *dc)
{
	t_player	tmp;

	tmp = *dc->player;
	*dc->player = *(vm->visu.drag_container.drag_union.drag_player.player);
	if (tmp.relevant)
		ft_swap(vm, dc, tmp);
	else
		ft_place(vm, dc);
	dispatch_players(vm, NULL);
}

void		ft_copy(t_vm *vm, t_drop_container *dc)
{
	int tmp;
	int rel;

	if (dc->player == &vm->client.upload_player)
		dc->player->color.value = 1;
	rel = dc->player->relevant;
	dc->player->relevant = 0;
	set_color_sdl(vm, dc->player);
	if (rel)
	{
		tmp = dc->player->num;
		*(dc->player) = *(vm->visu.drag_container.
				drag_union.drag_player.player);
		dc->player->num = tmp;
		dispatch_players(vm, dc->player);
	}
	else
	{
		*(dc->player) = *(vm->visu.drag_container.
				drag_union.drag_player.player);
		dispatch_players(vm, NULL);
	}
	dc->close->visible = 1;
}
