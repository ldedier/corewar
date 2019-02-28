/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:47:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/28 17:17:15 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_arena_players(t_vm *vm)
{
	int i;

	ft_render_title(vm, ARENA, vm->visu.center.dashboard_x +
			vm->visu.center.title_side, vm->visu.center.title_top);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, &(vm->player[i]),
		vm->visu.positions.arena_slots[i].player, ARENA);
		i++;
	}
	return (0);
}

int		ft_render_local_local_players(t_vm *vm)
{
	int i;

	ft_render_title(vm, LOCAL, vm->visu.center.dashboard_mid_x +
		vm->visu.center.title_side, vm->visu.center.title_top);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ft_render_player(vm, &(vm->local_player[i]),
		vm->visu.positions.local_slots[i].player, LOCAL);
		i++;
	}
	return (0);
}

int		ft_render_local_downloads_players(t_vm *vm, t_visu *v)
{
	t_list		*ptr;
	t_player	*player;
	t_xy		xy;

	ft_render_title(vm, DOWNLOADS, vm->visu.center.dashboard_mid_x +
		vm->visu.center.title_side, vm->visu.center.title_top);
	xy.x = v->center.dashboard_mid_x + v->center.player_left -
		(ft_to_print_scrollbar(v->players_list[DOWNLOADS].vscrollbar) ?
		v->center.scrollbar_width / 2 : 0);
	xy.y = vm->visu.center.title_top + vm->visu.center.title_h +
		vm->visu.center.title_bottom + vm->visu.center.player_top;
	ptr = v->downloaded_players;
	while (ptr != NULL)
	{
		player = ptr->content;
		ft_render_player(vm, player, xy, DOWNLOADS);
		xy.y += vm->visu.center.player_h + vm->visu.center.player_padding;
		ptr = ptr->next;
	}
	return (0);
}

int		ft_render_players(t_vm *vm)
{
	ft_render_arena_players(vm);
	if (vm->visu.local_type == LOCAL_LOCAL)
		ft_render_local_local_players(vm);
	else
		ft_render_local_downloads_players(vm, &vm->visu);
	return (0);
}
