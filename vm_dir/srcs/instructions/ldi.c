/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:45 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/26 19:33:12 by emuckens         ###   ########.fr       */
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
//	int		dest;

	val = 0;
//	if (!is_reg(arg[2].value))
//		return (FAILURE);
	ft_printf("arg0 val = %d arg1 val = %d\n", arg[0].value, arg[1].value);
	display_proc_ins(vm, proc);
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	arg[0].dest_value %= IDX_MOD;
	arg[1].dest_value %= IDX_MOD;
//	arg[1].dest_value = mod(arg[1].dest_value, IDX_MOD);
	ind = (arg[0].value + arg[1].value) % IDX_MOD;
	ft_printf("\narg 0 dest val = %d arg1 dest val = %d ldi: index = %d, proc pc = %d\n", arg[0].dest_value, arg[1].dest_value, ind, proc->pc);
	ind = mod(ind + proc->pc, MEM_SIZE);
	ft_printf("with pc, ind = %d\n", ind);
//	ind = mod((proc->pc + arg[0].dest_value + arg[1].dest_value), IDX_MOD);
//	if ((arg[1].value = mod(arg[1].value, IDX_MOD)) + proc->pc >= IDX_MOD)
//		arg[1].value -= IDX_MOD;
	i = -1;
	if (!vm->visu.active && (vm->display & (1 << MSG_INS)))
		ft_printf("\n%6s | -> load from %d + %d = %d (with pc and mod %d)", "", arg[0].value, arg[1].value, arg[0].value + arg[1].value, ind);
//	load_reg(vm, proc, arg[2].value, val);
	while (++i < REG_SIZE)
	{
		if (ind >= MEM_SIZE)
			ind -= MEM_SIZE;
		val <<= 8;
	ft_printf("ldi: index = %d\n", ind);
		val |= (unsigned char)vm->arena[ind];
	ft_printf("char val = %#x\n", (unsigned char)vm->arena[ind]);
		++ind;
	}
	proc->reg[arg[2].value - 1] = val;
	ft_printf("val to store in reg = %#x\n", val);
//	arg[0].retrieval_mode = 1;
//	arg[1].retrieval_mode = 1;
//	arg[2].retrieval_mode = 0;
	return (SUCCESS);
}
