/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/07 16:49:35 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ins_live(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	t_player *player;

	getval_param_dest(vm, proc, &arg[0], 1);
	player = get_player_num(vm->proc, arg[0].value);
	if (player)
	{
		proc->live = 1;
		player->live++;
		player->last_live_cycle = vm->total_cycle;
		vm->winner = player;
		++vm->live;
		ft_printf("un processus dit que le joueur %d (%s) est en vie.\n", player->num, player->name);
	}
	return (SUCCESS);
}
