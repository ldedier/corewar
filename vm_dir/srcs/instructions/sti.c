/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:18:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/22 20:47:55 by emuckens         ###   ########.fr       */
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

	getval_param_dest(vm, proc, &arg[0], 1);
	getval_param_dest(vm, proc, &arg[1], 1);
	getval_param_dest(vm, proc, &arg[2], 1);
//	ft_printf("val 0 = %d val 1 = %d val 2 = %d\n", arg[0].value, arg[1].value % MEM_SIZE, arg[2].value);
	dest = proc->pc + (arg[1].dest_value + arg[2].dest_value) % IDX_MOD;
	proc->pending.dest = vm->arena;
	proc->pending.dest_index = dest % MEM_SIZE; // pas certaine du %
//	ft_printf("dest index = %d\n", dest);
	proc->pending.value = (short)arg[0].dest_value;
	ft_printf("%6s | --> store to %d + %d = %d (with pc and mod %d)\n", "", arg[1].value, arg[2].value, arg[2].value + arg[1].value, dest % MEM_SIZE);
//	ft_printf("dest value = %#x\n", proc->pending.value);
	return (SUCCESS);
}
