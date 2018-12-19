/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 15:24:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add.valueue from registers # arg and # arg, store in register # arg
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 arg, all necessarily REGISTERS
** Returns failure if i.valueid register, success otherwise
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
