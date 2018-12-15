/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/15 16:27:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	getval_ind(t_vm *vm, t_process *proc, int index)
{
	int	val;

	ft_printf("indirect | index = %d\n", index);
	ft_memmove(&val, vm->arena + index, IND_SIZE);
	(void)proc;
	return (val);
}

static int	getval_reg(t_vm *vm, t_process *proc, int index)
{	
	ft_printf("reg | index = %d\n", index);
	return (*(int *)(vm->arena + proc->reg[index - 1]));
	(void)vm;
//	ft_printf("getval index = %d\n", index);
	return (proc->reg[index - 1]);
}

static int	getval_dir(t_vm *vm, t_process *proc, int val)
{
	ft_printf("direct\n");
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
