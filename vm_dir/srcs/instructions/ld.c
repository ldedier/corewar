/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:08:06 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/24 12:44:51 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [ld] instruction loads the value from the first argument to the register
** from second argument.
**
** Takes two arguments, the second one is necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
//	ft_printf("load val in reg %d\n", arg[1].value);
//	if (!is_reg(arg[1].value))
//		return (FAILURE);
//	ft_printf("0 val = %d dest val = %d 1 val = %d dest val = %d 2 val = %d dest val = %d\n", arg[0].value, arg[0].dest_value, arg[1].value, arg[1].dest_value, arg[2].value, arg[2].dest_value);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	load_reg(vm, proc, arg[1].value, arg[0].dest_value);
	proc->carry = !arg[0].dest_value;
	display_proc_ins(proc, arg[0].value, arg[1].value, arg[2].value);
//	display_registers(vm, proc);
	return (SUCCESS);
}
