/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 18:43:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** add arg2 and arg3.valueues, load arena content at the address off the sum into
** register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, two first necessarily INDEXES
** Returns failure if i.valueid register, success otherwise
*/

int		ins_ldi(t_vm *vm,  t_parameter arg[3], int pl)
{
	int sum;
	(void)sum;
	(void)vm;
	(void)pl;
	if (arg[FIRST].nb_bytes != T_IND || arg[SECOND].nb_bytes != T_IND)
		return (FAILURE); // verifier que c'est bien le cas
	sum = arg[SECOND].value + arg[FIRST].value; // verifier si verification taille en amont?
//	ft_memmove(proc->reg + arg[THIRD].value, (int)(&proc->pc - &(vm->arena)) + (sum % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
