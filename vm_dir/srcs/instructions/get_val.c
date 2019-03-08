/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 13:44:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static long	getval_ind(t_vm *vm, t_process *proc, int *index, int modulo)
{
	int	val;

	(void)proc;
	(void)modulo;
	val = getval_mod(vm->arena, mod(proc->pc + *index, MEM_SIZE),
		DIR_SIZE, MEM_SIZE);
	return (val);
}

static long	getval_reg(t_vm *vm, t_process *proc, int *index, int mod)
{
	(void)vm;
	(void)mod;
	return (proc->reg[*index - 1]);
}

static long	getval_dir(t_vm *vm, t_process *proc, int *val, int mod)
{
	(void)vm;
	(void)proc;
	(void)mod;
	return (*val);
}

void		getval_param_dest(t_vm *vm, t_process *proc,
												t_parameter *arg, int modulo)
{
	static long (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
		int *index, int mod) = {NULL, &getval_reg, &getval_dir, &getval_ind};

	if (arg->type == 0)
		return ;
	arg->dest_value = f_data[(int)arg->type](vm, proc, &arg->value, modulo);
}
