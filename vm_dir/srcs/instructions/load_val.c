/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/24 19:14:12 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void	load_arena(t_vm *vm, t_process *proc, int index, int val)
{
	int 	i;
	int		mod_index;
	int		byte_val;

	i = -1;
	mod_index = mod(index, MEM_SIZE);
	while (++i < DIR_SIZE)
	{
//	ft_printf("mod index = %d\n", mod_index);

		if (mod_index >= MEM_SIZE)
			mod_index -= MEM_SIZE;
		byte_val = val & (0xFF << ((3 - i) * 8));
		vm->arena[mod_index] = byte_val >> ((3 - i) * 8);
		vm->metarena[mod_index].color_index = proc->player->color.index;
		++mod_index;
	}
}

void	load_reg(t_vm *vm, t_process *proc, int num, int val)
{
	(void)vm;
	proc->reg[num - 1] = val;
}

/*
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
}*/
