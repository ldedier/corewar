/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:18:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/24 22:03:05 by emuckens         ###   ########.fr       */
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

	getval_param_dest(vm, proc, &arg[0], arg[0].value);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	getval_param_dest(vm, proc, &arg[2], IDX_MOD);
	arg[1].value = mod(arg[1].value, IDX_MOD);
	if (arg[1].value && arg[1].value + proc->pc > IDX_MOD)
		arg[1].value -= IDX_MOD;
	arg[2].type = DIR_CODE;
	dest = arg[1].value + arg[2].dest_value + proc->pc;
	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
	{
		display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].dest_value);
		ft_printf("\n%6s | -> store to %d + %d = %d (with pc and mod %d)", "", arg[1].value, arg[2].dest_value, arg[2].dest_value + arg[1].value, dest);
	}
	load_arena(vm, proc, mod(dest, MEM_SIZE), proc->reg[arg[0].value - 1]);
	return (SUCCESS);
}
