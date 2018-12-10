/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 16:30:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	getval_ind(t_vm *vm, t_process *proc, int index)
{
	(void)proc;
	return (vm->arena[index]);
}

static int	getval_reg(t_vm *vm, t_process *proc, int index)
{	
	(void)vm;
	return (proc->reg[index - 1]);
}

static int	getval_dir(t_vm *vm, t_process *proc, int val)
{
	(void)vm;
	(void)proc;
	return (val);
}

int			getval(t_vm *vm, t_process *proc, t_parameter arg)
{
	static int (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int index) = {NULL, &getval_reg, &getval_dir, &getval_ind};

	return (f_data[(int)arg.type](vm, proc, arg.value));
}
