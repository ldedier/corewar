/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/21 20:09:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static long	getval_ind(t_vm *vm, t_process *proc, int index, int mod)
{
	int	val;

	(void)proc;
	if (mod == IDX_MOD)
		index %= IDX_MOD;
	val = getval_mod(vm->arena, index, DIR_SIZE, MEM_SIZE);
	return (val);
}

static long	getval_reg(t_vm *vm, t_process *proc, int index, int mod)
{
	(void)vm;
	(void)mod;
	return (proc->reg[index - 1]);
}

static long	getval_dir(t_vm *vm, t_process *proc, int val, int mod)
{
	(void)vm;
	(void)proc;
	(void)mod;
	return (val);
}

void		getval_param_dest(t_vm *vm, t_process *proc,
												t_parameter *arg, int mod)
{
	static long (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int index, int mod) = {NULL, &getval_reg, &getval_dir, &getval_ind};

	arg->dest_value = f_data[(int)arg->type](vm, proc, arg->value, mod);
//	ft_printf("arg dest value = %#lx\n", arg->dest_value);
}
