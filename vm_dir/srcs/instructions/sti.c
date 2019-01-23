/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:18:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/23 21:43:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [sti] instruction loads value from register [arg 1] to arena at the adress
** [arg 2] + [arg 3].
**
** Takes 3 arguments, first one necessarily a REGISTER
*/

int		ins_sti(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int dest;

	ft_printf("arg 0 value = %d\n", arg[0].value);
	getval_param_dest(vm, proc, &arg[0], arg[0].value);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	getval_param_dest(vm, proc, &arg[2], IDX_MOD);

	ft_printf("val 0 = %d val 1 = %d val 2 = %d proc pc = %d\n", arg[0].value, arg[1].value, arg[2].value, proc->pc);
	ft_printf("DEST val 0 = %d val 1 = %d val 2 = %d proc pc = %d\n",arg[0].dest_value, arg[1].dest_value, arg[2].dest_value, proc->pc);
//	if ((arg[0].value = mod(arg[0].value, IDX_MOD)) > IDX_MOD)
//		arg[0].value -= IDX_MOD;
	if ((arg[1].value = mod(arg[1].value, IDX_MOD)) + proc->pc > IDX_MOD)
			arg[1].value -= IDX_MOD;
//	if ((arg[2].dest_value = mod(arg[2].dest_value, IDX_MOD)) > IDX_MOD)
//		arg[2].dest_value -= IDX_MOD;
	if ((dest = arg[1].dest_value + arg[2].dest_value + proc->pc) > IDX_MOD)
	{
		dest -= IDX_MOD;
	}
	ft_printf("dest = %d DEST val 0 = %d val 1 = %d val 2 = %d proc pc = %d\n", dest, arg[0].dest_value, arg[1].dest_value, arg[2].dest_value, proc->pc);
//	arg[1].value = dest;
//	ft_printf("reg 14 = %d\n", proc->reg[13]);
	proc->pending.dest = vm->arena;
	proc->pending.dest_index = dest; // pas certaine du %
//	ft_printf("dest index = %d\n", dest);
	proc->pending.value = arg[0].dest_value;
	ft_printf("pending value = %d\n", proc->pending.value);
//	ft_printf("%6s | --> store to %d + %d = %d (with pc and mod %d)\n", "", arg[1].value, arg[2].value, arg[2].value + arg[1].value, dest % MEM_SIZE);
//	ft_printf("dest value = %#x\n", proc->pending.value);
	return (SUCCESS);
}
