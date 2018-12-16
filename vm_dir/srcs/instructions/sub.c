/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 18:38:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Substracts two values from registers # arg 1 and # arg 2, and stores the
** result in register # arg 3.
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 args, all necessarily REGISTERS
** Returns failure if register value incorrect, success otherwise
*/

int		ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int	sub;

	(void)vm;
	if (check_reg(arg[FIRST]->value) || check_reg(arg[SECOND]->value)
					|| check_reg(arg[THIRD]->value))
				return (FAILURE);
	sub = proc->reg[arg[FIRST].value] - proc->reg[arg[SECOND].value];
	proc->reg[arg[THIRD].value] = sub;
	proc->carry = (!proc->reg[arg[THIRD].value]) ? 1 : 0;
	return (SUCCESS);
}
