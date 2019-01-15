/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 17:14:52 by uboumedj         ###   ########.fr       */
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
	if (!is_reg(arg[0].value) || !is_reg(arg[1].value)
			|| !is_reg(arg[2].value))
		return (FAILURE);
	sub = proc->reg[arg[0].value - 1] - proc->reg[arg[1].value - 1];
	proc->reg[arg[2].value - 1] = sub;
	proc->carry = !sub;
	return (SUCCESS);
}
