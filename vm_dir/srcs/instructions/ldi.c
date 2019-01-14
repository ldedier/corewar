/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/18 17:56:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [ldi] instruction loads content from arena at adress [arg 1] + [arg 2]
** then stores it in register [arg 3]
**
** Takes 3 arguments, first two necessarily INDEXES
*/

int		ins_ldi(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int sum;
	(void)sum;
	(void)arg;
	(void)proc;
	(void)vm;

//	sum = getval(vm, proc, arg[FIRST]);
//	sum += getval(vm, proc, arg[SECOND]);
//	loadval(vm, proc, arg[THIRD], *(vm->arena + sum % MEM_SIZE));

//	sum = arg->SECOND].value + arg->FIRST].value; // verifier si verification taille en amont?
//	ft_memmove(proc->reg + arg->THIRD].value, (int)(&proc->pc - &(vm->arena)) + (sum % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
