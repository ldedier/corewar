/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 23:09:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_render_server_players(t_vm *vm, double y)
{
	t_list			*ptr;
	t_client_slot	*slot;

	y += vm->visu.center.player_top;
	ptr = vm->client.client_slots;
	while (ptr != NULL)
	{
		slot = (t_client_slot *)(ptr->content);
		if (ft_render_client_slot(vm, slot, y))
			return (1);
		y += vm->visu.center.player_padding + vm->visu.center.player_h;
		ptr = ptr->next;
	}
	return (0);
}

int			ft_render_init_online(t_vm *vm)
{
	double y;

	y = vm->visu.center.top_dashboard_height +
		vm->visu.center.top_dashboard_fheight + vm->visu.center.title_top;
	if (ft_render_server_title(vm, y))
		return (1);
	y += vm->visu.center.s_title_h + vm->visu.center.title_bottom;
	if (ft_render_toolbar(vm, y))
		return (1);
	y += vm->visu.center.player_h + vm->visu.center.toolbar_bottom;
	ft_render_horizontal_line_dashboard(vm, y - 1, LINE_COL_DARKER);
	if (ft_render_server_players(vm, y))
		return (1);
	ft_render_horizontal_line_dashboard(vm, vm->visu.center.footer_y,
		LINE_COL);
	return (0);
}
