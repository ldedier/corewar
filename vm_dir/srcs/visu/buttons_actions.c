/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/20 15:43:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_delete_player(t_vm *vm, t_button *this, t_ixy xy)
{
	this->button_union.player->relevant = 0;
	dispatch_players(vm);
	this->visible = 0;
	ft_update_cursor(vm, xy);
}

void	fight(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	vm->visu.phase = PHASE_PLAY;
	ft_update_cursor(vm, xy);
}

void	nothing_on_click(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)vm;
	(void)this;
	(void)xy;
}

void	nothing_on_press(t_vm *vm, t_button *this)
{
	(void)vm;
	(void)this;
}

void	ft_upload(t_vm *vm, t_button *this, t_ixy mouse)
{
	(void)this;
	(void)mouse;
	vm->client.upload_player.relevant = 0;
	vm->visu.positions.upload_slot.close.visible = 0;
	this->enabled = 0;
}
