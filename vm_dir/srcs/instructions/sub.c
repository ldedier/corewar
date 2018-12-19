/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 15:25:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add value from registers # arg1 and # arg2, store in register #3
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 arg, all necessarily REGISTERS
** Returns failure if i.valueid register, success otherwise
*/

int		ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int	sub;

	(void)vm;
	sub = proc->reg[arg[0].value - 1] - proc->reg[arg[1].value - 1]; // verifier que la soustraction est bien dans ce sens
	proc->reg[arg[2].value - 1] = sub;
	proc->carry = !sub;
	return (SUCCESS);
}
