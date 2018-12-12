/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:35:05 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** add arg1 and arg2.values, load arena content at the address off the sum into
** register # arg3
** Input: vm (for arena and player), pl for process index,
** arg for 3 arg, two first necessarily INDEXES
*/

int		ins_ldi(t_vm *vm,  t_parameter arg[3], int pl)
{
	int sum;
	t_process	*proc;

	proc = get_proc_index(vm->proc, pl);
	sum = getval(vm, proc, arg[FIRST]);
	sum += getval(vm, proc, arg[SECOND]);
	loadval(vm, proc, arg[THIRD], *(vm->arena + sum % MEM_SIZE));

//	sum = arg->SECOND].value + arg->FIRST].value; // verifier si verification taille en amont?
//	ft_memmove(proc->reg + arg->THIRD].value, (int)(&proc->pc - &(vm->arena)) + (sum % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
