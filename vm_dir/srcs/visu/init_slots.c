/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:15:15 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 21:26:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_populate_upload_slot(t_vm *vm, t_visu *v)
{
	t_ixy xy;

	v->positions.upload_slot.player.x = v->center.dashboard_x +
		v->center.upload_left;
	v->positions.upload_slot.player.y = v->center.top_dashboard_height +
		v->center.top_dashboard_fheight +
		v->center.title_top + v->center.s_title_h + v->center.title_bottom;
	xy.x = v->positions.upload_slot.player.x + v->center.player_w -
			v->center.cross_border;
	xy.y = v->positions.upload_slot.player.y;
	ft_populate_closing_button(vm,
		&(v->positions.upload_slot.close), &vm->client.upload_player, xy);
	v->positions.upload_slot.close.vscrollbar =
		&vm->visu.players_list[UPLOAD].vscrollbar;
}

void	ft_populate_slot_position(t_vm *vm, t_visu *v, int i, double *y)
{
	t_ixy	xy;

	v->positions.arena_slots[i].player.x = v->center.dashboard_x +
		v->center.player_left -
		(ft_to_print_scrollbar(v->players_list[ARENA].vscrollbar) ? 
		 v->center.scrollbar_width / 2 : 0);
	v->positions.arena_slots[i].player.y = *y;
	xy.x = v->positions.arena_slots[i].player.x +
		v->center.player_w - v->center.cross_border;
	xy.y = *y;
	ft_populate_closing_button(vm, &(v->positions.arena_slots[i].close),
			&(vm->player[i]), xy);
	v->positions.local_slots[i].player.x = v->center.dashboard_mid_x +
		v->center.player_left -
		(ft_to_print_scrollbar(v->players_list[LOCAL].vscrollbar) ? 
		 v->center.scrollbar_width / 2 : 0);
	v->positions.local_slots[i].player.y = *y;
	*y += v->center.player_h + v->center.player_padding;
}

void    ft_populate_slots_positions(t_vm *vm, t_visu *v)
{
	int		i;
	double	y;

	y = v->center.title_top + v->center.title_h +
		v->center.title_bottom + v->center.player_top;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_populate_slot_position(vm, v, i, &y);
		i++;
	}
	ft_populate_upload_slot(vm, v);
}

void	ft_init_crosses(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			vm->visu.positions.arena_slots[i].close.visible = 1;
		i++;
	}
}

void	ft_init_client_slot_surface(t_vm *vm)
{
	t_list			*ptr;
	t_client_slot	*slot;

	ptr = vm->client.client_slots;
	while (ptr != NULL)
	{
		slot = (t_client_slot *)(ptr->content);
		slot->download.surface = vm->visu.sdl.images[DL];
		slot->download.vscrollbar = &vm->visu.players_list[SERVER].vscrollbar;
		ptr = ptr->next;
	}
}
