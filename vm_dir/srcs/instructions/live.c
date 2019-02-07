/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:34 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/07 18:32:47 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [live] instruction declares the player whose number is [arg 1] alive.
**
** Takes 1 argument: the player's number. Undetermined behaviour if [arg 1]
** isn't a known player number.
*/

int		ins_live(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	t_player	*player;
	t_fade		*live;

	getval_param_dest(vm, proc, &arg[0], 1);
	proc->live = 1;
	++vm->issued_live;
	proc->live_cycle = vm->total_cycle; // enlever, gere par proc->pending_ins.op
	player = get_player_num(vm, vm->proc, arg[0].value);
	arg[0].retrieval_mode = 0;
	display_proc_ins(vm, proc);
	if (player)
	{
		++vm->live;
		player->live++;
		player->last_live_cycle = vm->total_cycle;
		vm->winner = player;
		live = (t_fade *)ft_memalloc(sizeof(t_fade));
		live->pc = proc->pc;
		live->color = *(int *)player->color.value;
		live->value = FADE_LEN;
		display_player_alive(vm, player);
		if (ft_add_to_list_ptr(&vm->live_ok, (void *)live, sizeof(t_fade)))
			return (FAILURE);
	}
	return (SUCCESS);
}
