/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:17:30 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/04 22:43:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [or] instruction executes a bitwise OR between [arg 1] and [arg2],
** then stores the result in the register given in [arg 3].
**
** Takes three arguments, third one is necessarily a REGISTER
*/

int		ins_or(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		res;

	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	res = arg[0].dest_value | arg[1].dest_value;
	load_reg(vm, proc, arg[2].value, res);
	proc->carry = !res;
	arg[0].retrieval_mode = 1;
	arg[1].retrieval_mode = 1;
	arg[2].retrieval_mode = 0;
	display_proc_ins(vm, proc);
	return (SUCCESS);
}
