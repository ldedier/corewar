/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:24:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add.valueue from registers # arg and # arg, store in register # arg
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 arg, all necessarily REGISTERS
** Returns failure if i.valueid register, success otherwise
*/

int		ins_add(t_vm *vm, t_parameter arg[3], int pl)
{
	int sum;
	t_process	*proc;

	(void)vm;
	proc = get_proc_index(vm->proc, pl);
//	if (arg[FIRST]->value >= REG_NUMBER
//			|| arg[SECOND]->value >= REG_NUMBER
//			|| arg[THIRD]->value >= REG_NUMBER)
//		return (FAILURE); // verifier que c'est bien le cas
	sum = proc->reg[arg[FIRST].value] + proc->reg[arg[SECOND].value];
	proc->reg[arg[THIRD].value] = sum; 
	return (SUCCESS);
}
