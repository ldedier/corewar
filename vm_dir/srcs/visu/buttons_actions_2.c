/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 16:19:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
