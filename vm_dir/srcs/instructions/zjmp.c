/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:31 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/25 16:28:14 by emuckens         ###   ########.fr       */
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
	arg[0].retrieval_mode = 0;
	if (vm->display & (1 << MSG_INS))
		display_proc_ins(vm, proc);
	arg[0].value %= IDX_MOD;
	if (proc->carry)
	{

		proc->pc = mod(arg[0].value + proc->pc, MEM_SIZE);
		if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
			ft_printf(" OK");
	}
	else if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		ft_printf(" FAILED");
	return (SUCCESS);
}
