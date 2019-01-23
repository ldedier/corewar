/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/23 19:40:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**static void	load_arena(t_vm *vm, t_process *proc, t_parameter *arg, int val)
**{
**	int 	i;
**	int		index;
**
**	i = -1;
**	index = arg->value + proc->pc;
**	while (++i < DIR_SIZE)
**	{
**		vm->arena[(index + i) % MEM_SIZE] =
**					(val & (0xFF << (8 * (3 - i)))) >> ((3 - i) * 8);
**		vm->metarena[(index + i) % MEM_SIZE].color_index =
**										*(int *)proc->player->color.value;
**	}
**}
**
**static void	load_reg(t_vm *vm, t_process *proc, t_parameter *arg, int val)
**{
**	proc->reg[arg->value - 1] = val;
**}
*/

void	loadval(t_vm *vm, t_process *proc, t_parameter *arg, int val)
{
//	ft_printf("load val arg value = %d val = %d\n", arg->value, val);
	if (arg->type == 1)
	{
		proc->pending.dest = proc->reg;
		proc->pending.dest_index = arg->value - 1;
//	ft_printf("load val arg value = %d\n", arg->value);
	}
	else if (arg->type > 1)
	{
		proc->pending.dest = vm->arena;
		proc->pending.dest_index = arg->value + proc->pc;
//	ft_printf("load val arg value = %d\n", arg->value);
	}
//	ft_printf("proc pending dest = %d val = %d\n", proc->pending.dest_index, val);
	proc->pending.value = val;
//	if (proc->pending.ins.op.opcode == LD)
//		ft_printf("pending value = %d\n", val);
}
