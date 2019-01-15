/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:17:30 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/14 17:15:11 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [or] instruction executes a bitwise OR between [arg 1] and [arg2],
** then stores the result in the register given in [arg 3].
**
** Takes three arguments, third one is necessarily a REGISTER
** Returns failure if register value is incorrect.
*/

int		ins_or(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		res;

	if (!is_reg(arg[2].value))
		return (FAILURE);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	res = arg[0].dest_value | arg[1].dest_value;
	loadval(vm, proc, &arg[2], res);
	proc->carry = res ? 0 : 1;
	return (SUCCESS);
}
