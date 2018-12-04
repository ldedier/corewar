/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 14:51:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add value from registers # arg1 and # arg2, store in register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, all necessarily REGISTERS
** Returns failure if invalid register, success otherwise
*/

int		ins_sub(t_vm *vm, t_process *proc, t_arg arg[3])
{
	int	sub;

	(void)vm;
	if (arg[FIRST].val >= REG_NUMBER
			|| arg[SECOND].val >= REG_NUMBER
			|| arg[THIRD].val >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	sub = proc->reg[arg[FIRST].val] - proc->reg[arg[SECOND].val]; // verifier que la soustraction est bien dans ce sens
	proc->reg[arg[THIRD].val] = sub;
	return (SUCCESS);
}
