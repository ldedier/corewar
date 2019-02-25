/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:09:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/20 19:56:57 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [lfork] instruction creates a new process at the address [arg 1], with the
** same state as the calling process excepted the PC (unless [arg 1] is 0),
** without the IDX_MOD distance restriction.
**
** Takes 1 argument: the address at which the new process must start.
*/

int		ins_lfork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	add_process(vm, 0, 0, proc);
	getval_param_dest(vm, proc, &arg[0], arg[0].value);
	arg[0].retrieval_mode = 0;
	display_proc_ins(vm, proc);
	if (!vm->visu.active && vm->display & (1 << MSG_INS))
		ft_printf(" (%d)", proc->pc + arg[0].value);
	((t_process *)vm->proc->content)->pc = mod(proc->pc + arg[0].value, MEM_SIZE);
	return (SUCCESS);
}
