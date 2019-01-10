/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:39:43 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/10 16:40:14 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [and] instruction executes a bitwise AND between arg1 and arg2, and stores
** the result in the register given in the third argument.
**
** Takes 3 arguments, third one is necessarily a REGISTER
*/

int		ins_and(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		res;

	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	res = arg[0].dest_value & arg[1].dest_value;
	loadval(vm, proc, &arg[2], res);
	proc->carry = res ? 0 : 1;
	return (SUCCESS);
}
