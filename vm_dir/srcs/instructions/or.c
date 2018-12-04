/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 18:41:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** check for bitwise | between arg1 and arg2, store result in register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, arg3 necessarily a REGISTER
** Returns failure if invalid register, success otherwise
*/

int		ins_or(t_vm *vm, t_process *proc, t_arg arg[3])
{
	(void)vm;
	if (arg[THIRD].val >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	proc->reg[arg[THIRD].val] = arg[FIRST].val | arg[SECOND].val;
	return (SUCCESS);
}
