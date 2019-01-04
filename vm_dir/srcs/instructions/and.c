/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:39:43 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/04 17:39:51 by uboumedj         ###   ########.fr       */
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
	proc->reg[arg[2].value - 1] = arg[0].value & arg[1].value;
	proc->carry = !(proc->reg[arg[2].value - 1]);
	return (SUCCESS);
}
