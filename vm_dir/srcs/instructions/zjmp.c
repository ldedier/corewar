/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:31 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/06 11:57:32 by emuckens         ###   ########.fr       */
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
//	ft_printf("ZJMP check arg 0 val = %d dest val = %d proc pc = %d\n", arg[0].value, arg[0].dest_value, proc->pc);
//	if ((arg[0].value + proc->pc) >= IDX_MOD)
//		arg[0].value -= IDX_MOD;
	arg[0].retrieval_mode = 0;
//	if (arg[0].value > 255) // EUHHHHH
//		arg[0].value -= IDX_MOD;
//	ft_printf("proc pc = %d dest value = %d\n", proc->pc, arg[0].dest_value);
//	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		display_proc_ins(vm, proc);
		arg[0].value %= IDX_MOD;
	if (proc->carry)
	{

//		ft_printf("proc pc = %d, arg0 value = %d\n", proc->pc, arg[0].value);
		proc->pc = mod(arg[0].value + proc->pc, MEM_SIZE);
		if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
			ft_printf(" OK");
//		arg[0].value = (proc->pending.pc + proc->pc) % IDX_MOD;
//		ft_printf("proc pc = %d proc pending pc = %d\n", proc->pc, proc->pending.pc);
//		if (proc->pending.pc + proc->pc < 0)
//		{
	//		arg[0].value += IDX_MOD;
//			proc->pending.pc += IDX_MOD;
//		}
//		ft_printf("AFTER proc pc = %d proc pending pc = %d\n", proc->pc, proc->pending.pc);
	}
	else if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		ft_printf(" FAILED");
	return (SUCCESS);
}
