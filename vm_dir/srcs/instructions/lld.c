/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:30:07 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 19:26:08 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [lld] instruction loads the value from the first argument to the register
** from second argument, without the IDX_MOD distance restriction.
**
** Takes two arguments, the second one is necessarily a REGISTER
*/

int		ins_lld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 0);
	load_reg(vm, proc, arg[1].value, arg[0].dest_value);
	proc->carry = !arg[0].dest_value;
	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].value);
	return (SUCCESS);
}
