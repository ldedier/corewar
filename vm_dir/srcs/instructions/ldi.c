/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:45 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/06 14:25:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [ldi] instruction loads content from arena at adress [arg 1] + [arg 2]
** then stores it in register [arg 3]
**
** Takes 3 arguments, first two necessarily INDEXES
*/

static void	ldi_val(t_vm *vm, int *ind, int *val)
{
	int i;

	i = -1;
	while (++i < REG_SIZE)
	{
		if (*ind >= MEM_SIZE)
			*ind -= MEM_SIZE;
		*val <<= 8;
		*val |= (unsigned char)vm->arena[*ind];
		++(*ind);
	}
}

int			ins_ldi(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		ind;
	int		val;

	val = 0;
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	arg[0].retrieval_mode = 1;
	arg[1].retrieval_mode = 1;
	display_proc_ins(vm, proc);
	ind = (arg[0].dest_value + arg[1].dest_value) % IDX_MOD + proc->pc;
	if ((vm->display.code & (1 << MSG_INS)))
		ft_printf("\n%6s | -> load from %d + %d = %d (with pc and mod %d)", "",
				arg[0].dest_value, arg[1].dest_value,
				arg[0].dest_value + arg[1].dest_value, ind);
	arg[0].dest_value %= IDX_MOD;
	arg[1].dest_value %= IDX_MOD;
	ldi_val(vm, &ind, &val);
	proc->reg[arg[2].value - 1] = val;
	return (SUCCESS);
}
