/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/08 18:28:23 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		load_arena(t_vm *vm, t_process *proc, t_parameter *arg, int val)
{
	int 	i;
	int		index;
	
	i = -1;
	index = arg->value + proc->pc;
//	ft_printf("load in arena, index = %d pc = %d, val = %d\n", arg->value, proc->pc, val); 
	while (++i < DIR_SIZE)
	{
//		ft_printf("i = %d index = %d 0xff << machin = %#x & val = %#x\n", i, index + i, 0xFF << (8 * (3 - i)), val & (0xFF << (8 * (3 - i))));
		vm->arena[(index + i) % MEM_SIZE] = (val & (0xFF << (8 * (3 - i)))) >> ((3 - i) * 8);
//		ft_printf("vm arena in %d = %d\n", (index + i) % MEM_SIZE, vm->arena[(index + i) % MEM_SIZE]);
	}
}

static void		load_reg(t_vm *vm, t_process *proc, t_parameter *arg, int val)
{
//	ft_printf("load in reg, index = %d val = %d\n", arg->dest_value, val);
	proc->reg[arg->value - 1] = val;
//	ft_printf("check proc reg = %d\n", proc->reg[arg->value - 1]);
	vm->metarena[arg->value - 1].color_index = proc->player->color.index;
}

void		loadval(t_vm *vm, t_process *proc, t_parameter *arg, int val)
{
	static void	(*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc, t_parameter *arg, int val) = {
		NULL, &load_reg, &load_arena, &load_arena};

//	ft_printf("in load val, val = %d arg->type = %d\n", val, arg->type);
	f_data[(int)arg->type](vm, proc, arg, val);
}


