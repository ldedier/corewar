/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:18:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/07 20:50:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [sti] instruction loads value from register [arg 1] to arena at the adress
** [arg 2] + [arg 3].
**
** Takes 3 arguments, first one necessarily a REGISTER
*/

int		ins_sti(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int dest;
	getval_param_dest(vm, proc, &arg[0], arg[0].value);
	getval_param_dest(vm, proc, &arg[1], arg[1].value);
	getval_param_dest(vm, proc, &arg[2], arg[2].value);

	arg[1].retrieval_mode = 1;
	arg[2].retrieval_mode = 1;
	display_proc_ins(vm, proc);
	dest = (arg[1].dest_value + arg[2].dest_value);
	dest %= IDX_MOD;
	load_arena(vm, proc, dest + proc->pc, proc->reg[arg[0].value - 1]);
	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		ft_printf("\n%6s | -> store to %d + %d = %d (with pc and mod %d)", "",
				arg[1].dest_value, arg[2].dest_value, dest, dest % IDX_MOD + proc->pc);
	return (SUCCESS);
}
