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
** add arg2 and arg3 values, load arena content at the address off the sum into 
** register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, two first necessarily INDEXES
** Returns failure if invalid register, success otherwise
*/

int		ins_ldi(t_vm *vm, t_process *proc, t_arg arg[3])
{
	int sum;
	if (arg[FIRST].nb_bytes != T_IND || arg[SECOND].nb_bytes != T_IND)
		return (FAILURE); // verifier que c'est bien le cas
	sum = arg[SECOND].val + arg[FIRST].val; // verifier si verification taille en amont?
	ft_memmove(proc->reg + arg[THIRD].val, vm->arena + proc->pc + (sum % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
