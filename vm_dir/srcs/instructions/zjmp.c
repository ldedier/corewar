/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/08 16:01:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [zjmp] instruction jumps PC to address [arg 1] if carry is ON (value = 1)
**
** Takes 1 argument: the address.
*/

int		ins_zjmp(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 1);
	ft_printf("dest val = %d dest val mod idxmod = %d pc = %d\n",
		arg[0].dest_value % MEM_SIZE, arg[0].dest_value % IDX_MOD, proc->pc);
	if (proc->carry)
	{
		proc->pending.pc = (arg[0].dest_value);
	}
	return (SUCCESS);
}
