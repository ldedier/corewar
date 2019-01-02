/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/02 17:46:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_delete_player(t_vm *vm, t_button *this, t_ixy xy)
{
	this->button_union.player->relevant = 0;
	dispatch_players(vm, NULL);
	this->visible = 0;
	ft_update_cursor(vm, xy);
	return (0);
}

int		start_fight(t_vm *vm)
{
	vm->visu.phase = PHASE_PLAY;
	if (!init_processes(vm))
		 return (1);
	return (0);
}

int		fight(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	if (start_fight(vm))
		return (1);
	ft_update_cursor(vm, xy);
	return (0);
}

int		clean_arena(t_vm *vm, t_button *this, t_ixy xy)
{
	int i;

	(void)this;
	(void)xy;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->visu.positions.arena_slots[i].close.visible = 0;
		i++;
	}
	dispatch_players(vm, NULL);
	return (0);
}

int		switch_local(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	(void)xy;
	if (vm->visu.local_type == LOCAL_LOCAL)
	{
		vm->visu.players_list[LOCAL].vscrollbar.relevant = 0;
		vm->visu.players_list[DOWNLOADS].vscrollbar.relevant = 1;
		vm->visu.players_list[DOWNLOADS].vscrollbar.state = 0;
		vm->visu.local_type = LOCAL_DOWNLOAD;
	}
	else
	{
		vm->visu.players_list[DOWNLOADS].vscrollbar.relevant = 0;
		vm->visu.players_list[LOCAL].vscrollbar.relevant = 1;
		vm->visu.players_list[LOCAL].vscrollbar.state = 0;
		vm->visu.local_type = LOCAL_LOCAL;
	}
	return (0);
}

int		nothing_on_click(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)vm;
	(void)this;
	(void)xy;
	return (0);
}

void	nothing_on_press(t_vm *vm, t_button *this)
{
	(void)vm;
	(void)this;
}

int		ft_upload(t_vm *vm, t_button *this, t_ixy mouse)
{
	(void)this;
	(void)mouse;

	if (vm->client.upload_player.from_server)
		ft_set_notification(vm, FROM_SERVER_NOTIF);
	else
		ft_process_upload(vm, vm->client.upload_player);
	vm->client.upload_player.relevant = 0;
	vm->visu.positions.upload_slot.close.visible = 0;
	this->enabled = 0;
	return (0);
}
