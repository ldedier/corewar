/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 12:00:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [sub] instruction substracts two values from registers [arg 1] and [arg 2]
** and stores the result in register [arg 3].
**
** Takes three arguments, all necessarily REGISTERS
** Returns failure if register values are incorrect.
*/

int		ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int	sub;

	(void)vm;
	if (!is_reg(arg[0].value) || !is_reg(arg[1].value) || !is_reg(arg[2].value))
		return (FAILURE);
	sub = proc->reg[arg[0].value - 1] - proc->reg[arg[1].value - 1];
	load_reg(vm, proc, arg[2].value, sub);
//	proc->reg[arg[2].value - 1] = sub;
	proc->carry = !sub;
	display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].value);
	return (SUCCESS);
}
