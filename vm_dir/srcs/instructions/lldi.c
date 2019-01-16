/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:15:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/10 17:15:43 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [lldi] instruction loads content from arena at adress [arg 1] + [arg 2],
** without the IDX_MOD distance restriction, then stores it in register [arg 3]
**
** Takes 3 arguments, first two necessarily INDEXES
*/

int		ins_lldi(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		ind;
	int		val;

	if (!is_reg(arg[2].value))
		return (FAILURE);
	getval_param_dest(vm, proc, &arg[0], 0);
	getval_param_dest(vm, proc, &arg[1], 0);
	ind = proc->pc + (arg[0].dest_value + arg[1].dest_value);
	val = getval_mod(vm->arena, ind, DIR_SIZE, MEM_SIZE);
	loadval(vm, proc, &arg[2], val);
	proc->carry = !val;
	return (SUCCESS);
}
