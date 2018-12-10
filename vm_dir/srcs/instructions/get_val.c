/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/09 21:01:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	getval_ind(t_vm *vm, t_process *proc, int index, int size)
{
	(void)proc;
	return (vm->arena[index]);
}

static int	getval_reg(t_vm *vm, t_process *proc, int index, int size)
{	
	(void)vm;
	return (proc->reg[index - 1]);
}

static int	getval_dir(t_vm *vm, t_process *proc, int val, int)
{
	(void)vm;
	(void)proc;
	return (val);
}

int			getval(t_vm *vm, t_process *proc, t_parameter arg)
{
	static int (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int val) = {NULL, &getval_reg, &getval_dir, &getval_ind};

	return (f_data[(int)arg.type](vm, proc, arg.value, sizeof(arg.value)));
}
