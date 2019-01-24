/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:17:46 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 12:11:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [xor] instruction executes a bitwise XOR between [arg 1] and [arg2],
** then stores the result in the register given in [arg 3].
**
** Takes three arguments, third one is necessarily a REGISTER
** Returns failure if register value is incorrect.
*/

int		ins_xor(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		res;

	if (!is_reg(arg[2].value))
		return (FAILURE);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	res = arg[0].dest_value ^ arg[1].dest_value;
	load_reg(vm, proc, arg[2].value, res);
	proc->carry = res ? 0 : 1;
	display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].value);
	return (SUCCESS);
}
