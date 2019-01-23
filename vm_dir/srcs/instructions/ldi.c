/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:45 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/23 20:04:00 by emuckens         ###   ########.fr       */
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
	int		val;

	val = 0;
	if (!is_reg(arg[2].value))
		return (FAILURE);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
//	ft_printf("\"arg0 val = %d dest = %d\n", arg[0].value, arg[0].dest_value);
//	ft_printf("arg1 val = %d dest = %d\n", arg[1].value, arg[1].dest_value);
//	ft_printf("arg2 val = %d dest = %d\n", arg[2].value, arg[2].dest_value);
	ind = mod((arg[0].dest_value + arg[1].dest_value), IDX_MOD);
	arg[1].value = mod(arg[1].value, IDX_MOD);
	if (ind + proc->pc >= IDX_MOD)
		arg[1].value -= IDX_MOD;
	val = proc->reg[arg[2].dest_value - 1];
//	ft_printf("ldi | ind = %d, val = %#x\n", ind, val);
	loadval(vm, proc, &arg[2], val);
	return (SUCCESS);
}
