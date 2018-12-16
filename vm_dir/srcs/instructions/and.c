/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 18:38:54 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** check for bitwise & between arg1 and arg2, store result in register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 args, arg-> necessarily a REGISTER
*/

int		ins_and(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	(void)vm;
	if (check_reg(arg[THIRD].value))
		return (FAILURE);
	proc->reg[arg[THIRD].value] = arg[FIRST].value & arg[SECOND].value;
	return (SUCCESS);
}
