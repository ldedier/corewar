/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   download.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:14:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 18:14:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_download(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)xy;
	(void)vm;
	if (!this->button_union.client_slot->on_disk)
	{
		if (ft_query_player_bin(vm, this->button_union.client_slot))
			return (1);
		ft_lst_mergesort(&vm->visu.downloaded_players, &ft_sort_alpha, 0);
	}
	this->enabled = 0;
	this->button_union.client_slot->on_disk = 1;
	return (0);
}

void	ft_populate_download_button(t_vm *vm, t_client_slot *client_slot,
		t_button *button)
{
	button->visible = 1;
	button->enabled = 1;
	button->button_union.client_slot = client_slot;
	button->on_click = &ft_download;
	button->on_press = &nothing_on_press;
	button->surface = vm->visu.sdl.images[DL];
	button->vscrollbar = &vm->visu.players_list[SERVER].vscrollbar;
	button->render = &ft_render_download_button;
	button->phase = PHASE_INIT;
}
