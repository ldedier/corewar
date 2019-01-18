/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_client.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:49:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 19:55:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		sort_alpha(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	(void)xy;
	if (vm->visu.sort_cs_func == &ft_sort_alpha_cs)
		vm->visu.inv_sort = !vm->visu.inv_sort;
	else
	{
		vm->visu.inv_sort = 0;
		vm->visu.sort_cs_func = &ft_sort_alpha_cs;
	}
	vm->visu.players_list[SERVER].vscrollbar.state = 0;
	ft_sort_client_slots(vm);
	return (0);
}

int		sort_score(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	(void)xy;
	if (vm->visu.sort_cs_func == &ft_sort_score_cs)
		vm->visu.inv_sort = !vm->visu.inv_sort;
	else
	{
		vm->visu.inv_sort = 0;
		vm->visu.sort_cs_func = &ft_sort_score_cs;
	}
	vm->visu.sort_cs_func = &ft_sort_score_cs;
	vm->visu.players_list[SERVER].vscrollbar.state = 0;
	ft_sort_client_slots(vm);
	return (0);
}

int		ft_upload(t_vm *vm, t_button *this, t_ixy mouse)
{
	(void)this;
	(void)mouse;
	if (vm->client.upload_player.from_server)
		ft_set_notification(vm, FROM_SERVER_NOTIF);
	else if (out_of_atlas_range(vm->client.upload_player.name))
		ft_set_notification(vm, NAME_INVALID_NOTIF);
	else
		ft_process_upload(vm, vm->client.upload_player);
	vm->client.upload_player.relevant = 0;
	vm->visu.positions.upload_slot.close.visible = 0;
	this->enabled = 0;
	return (0);
}
