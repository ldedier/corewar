/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/28 20:08:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static long	getval_ind(t_vm *vm, t_process *proc, int *index)
{
	int	val;
	int pc;

	(void)proc;
	pc = mod(proc->pc + *index, MEM_SIZE);
	val = getval_mod(vm->arena, pc, DIR_SIZE, MEM_SIZE);
	return (val);
}

static long	getval_reg(t_vm *vm, t_process *proc, int *index)
{
	(void)vm;
	return (proc->reg[*index - 1]);
}

static long	getval_dir(t_vm *vm, t_process *proc, int *val)
{
	(void)vm;
	(void)proc;
	return (*val);
}

void		getval_param_dest(t_vm *vm, t_process *proc,
												t_parameter *arg)
{
	static long (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int *index) = {NULL, &getval_reg, &getval_dir, &getval_ind};

	if (arg->type == 0)
		return ;
	arg->dest_value = f_data[(int)arg->type](vm, proc, &arg->value);
}
