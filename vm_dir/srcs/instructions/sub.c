/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/14 20:24:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [sub] instruction substracts two values from registers [arg 1] and [arg 2]
** and stores the result in register [arg 3].
**
** Takes three arguments, all necessarily REGISTERS
*/

int		ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int	sub;

	sub = proc->reg[arg[0].value - 1] - proc->reg[arg[1].value - 1];
	load_reg(vm, proc, arg[2].value, sub);
	arg[0].retrieval_mode = 0;
	arg[1].retrieval_mode = 0;
	arg[2].retrieval_mode = 0;
	proc->carry = !sub;
	display_proc_ins(vm, proc);
	return (SUCCESS);
}
