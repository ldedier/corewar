/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:30:07 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/14 20:00:40 by emuckens         ###   ########.fr       */
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
	arg[0].retrieval_mode = 1;
	arg[1].retrieval_mode = 0;
	display_proc_ins(vm, proc);
	return (SUCCESS);
}
