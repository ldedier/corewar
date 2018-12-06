/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 14:47:36 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add.valueue from registers # arg1 and # arg2, store in register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, all necessarily REGISTERS
** Returns failure if i.valueid register, success otherwise
*/

int		ins_add(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int sum;

	(void)vm;
	if (arg[FIRST].value >= REG_NUMBER
			|| arg[SECOND].value >= REG_NUMBER
			|| arg[THIRD].value >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	sum = proc->reg[arg[FIRST].value] + proc->reg[arg[SECOND].value];
	proc->reg[arg[THIRD].value] = sum; 
	return (SUCCESS);
}