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
** Substracts two values from registers # arg 1 and # arg 2, and stores the
** result in register # arg 3.
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 args, all necessarily REGISTERS
** Returns failure if register value incorrect, success otherwise
*/

int		ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int	sub;

	(void)vm;
	sub = proc->reg[arg[0].value - 1] - proc->reg[arg[1].value - 1];
	proc->reg[arg[2].value - 1] = sub;
	proc->carry = !sub;
	return (SUCCESS);
}
