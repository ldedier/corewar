/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:38:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 17:15:43 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [add] instruction adds two values from registers [arg 1] and [arg 2], then
** stores the result in register [arg 3].
**
** Takes three arguments, all necessarily REGISTERS
** Returns failure if register values are incorrect.
*/

int		ins_add(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int sum;

	(void)vm;
	if (!is_reg(arg[0].value) || !is_reg(arg[1].value)
			|| !is_reg(arg[2].value))
		return (FAILURE);
	sum = proc->reg[arg[0].value - 1] + proc->reg[arg[1].value - 1];
	proc->reg[arg[2].value - 1] = sum;
	proc->carry = !sum;
	return (SUCCESS);
}
