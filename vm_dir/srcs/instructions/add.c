/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:38:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 17:39:19 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add two values from registers # arg 1 and # arg 2, and stores the result
** in register # arg 3.
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 args, all necessarily REGISTERS
** Returns failure if register value incorrect, success otherwise
*/

int		ins_add(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int sum;

	(void)vm;
	sum = proc->reg[arg[0].value - 1] + proc->reg[arg[1].value - 1];
	proc->reg[arg[2].value - 1] = sum;
	proc->carry = !sum;
	return (SUCCESS);
}
