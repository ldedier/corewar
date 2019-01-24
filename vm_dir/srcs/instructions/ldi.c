/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:45 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 19:38:12 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [ldi] instruction loads content from arena at adress [arg 1] + [arg 2]
** then stores it in register [arg 3]
**
** Takes 3 arguments, first two necessarily INDEXES
*/

int		ins_ldi(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		ind;
	int		i;
	int		val;

	val = 0;
//	if (!is_reg(arg[2].value))
//		return (FAILURE);
//	ft_printf("\"arg0 val = %d dest = %d\n", arg[0].value, arg[0].dest_value);
//	ft_printf("arg1 val = %d dest = %d\n", arg[1].value, arg[1].dest_value);
//	ft_printf("arg2 val = %d dest = %d\n", arg[2].value, arg[2].dest_value);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
//	arg[1].value += proc->pc;
//	arg[1].type = IND_CODE;
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	ind = mod((proc->pc + arg[0].dest_value + arg[1].dest_value), IDX_MOD);
//	ft_printf("pc = %d ind = %d\n", proc->pc, ind);
	if ((arg[1].value = mod(arg[1].value, IDX_MOD)) + proc->pc >= IDX_MOD)
//	if (ind + proc->pc >= IDX_MOD)
		arg[1].value -= IDX_MOD;
//	val = proc->reg[arg[2].dest_value - 1];
//	ft_printf("ldi | ind = %#x\n", ind);
	i = -1;
	while (++i < REG_SIZE)
	{
		if (ind >= IDX_MOD)
			ind -= IDX_MOD;
		val = val << 8;
		val |= (unsigned char)vm->arena[mod(ind, IDX_MOD)];
//		ft_printf("ind = %d arena[ind] = %#x val = %#x\n", ind, vm->arena[ind], val);
		++ind;
	}

	load_reg(vm, proc, arg[2].value, val);
	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
	{
		display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].value);
	ft_printf("\n%6s | -> %.4s from %d + %d = %d (with pc and mod %d)", "", proc->pending_ins.op.description, proc->pending_ins.params[0].value, proc->pending_ins.params[1].value, proc->pending_ins.params[0].value + proc->pending_ins.params[1].value, mod(proc->pc + proc->pending_ins.params[1].value + proc->pending_ins.params[0].value, MEM_SIZE));
	}
	return (SUCCESS);
}
