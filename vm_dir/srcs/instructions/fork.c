/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:28 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/28 15:53:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [fork] instruction creates a new process at the address [arg 1], with the
** same state as the calling process excepted the PC obviously
** (unless [arg 1] is 0)
**
** Takes 1 argument: the address at which the new process must start.
*/

int		ins_fork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	add_process(vm, 0, 0, proc);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	arg[0].retrieval_mode = 0;
	display_proc_ins(vm, proc);
	arg[0].value %= IDX_MOD;
	if (!vm->visu.active && (vm->display.code & (1 << MSG_INS)))
		ft_printf(" (%d)", proc->pc + arg[0].value);
	((t_process *)vm->proc->content)->pc = mod(proc->pc + arg[0].value, MEM_SIZE);
	return (SUCCESS);
}
