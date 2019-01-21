/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/21 16:41:55 by emuckens         ###   ########.fr       */
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
	if (arg->type == 1)
	{
		proc->pending.dest = proc->reg;
		proc->pending.dest_index = arg->value - 1;
	}
	else if (arg->type > 1)
	{
		proc->pending.dest = vm->arena;
		proc->pending.dest_index = arg->value + proc->pc;
	}
	proc->pending.value = val;
}
