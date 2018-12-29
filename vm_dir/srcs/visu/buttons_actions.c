/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/21 19:34:01 by ldedier          ###   ########.fr       */
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
	vm->client.upload_player.relevant = 0;
	vm->visu.positions.upload_slot.close.visible = 0;
	this->enabled = 0;
	return (0);
}
