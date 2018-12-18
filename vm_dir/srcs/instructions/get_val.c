/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/18 20:31:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	getval_ind(t_vm *vm, t_process *proc, int index)
{
	int	val;

	(void)proc;
	val = getval_mod(vm->arena, index, IND_SIZE, MEM_SIZE);
	ft_printf("indirect | index = %d\n", index);
	return (val);
}

static int	getval_reg(t_vm *vm, t_process *proc, int index)
{	
	ft_printf("reg | index = %d\n", index);
	(void)vm;
	return (proc->reg[index - 1]);
}

static int	getval_dir(t_vm *vm, t_process *proc, int val)
{
	ft_printf("direct\n");
	(void)vm;
	(void)proc;
	return (val);
}

void		getval_param_dest(t_vm *vm, t_process *proc, t_parameter arg[3], int nb_params)
{
	static int (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int index) = {NULL, &getval_reg, &getval_dir, &getval_ind};
	int i;

	i = -1;
	while (++i < nb_params)
	{
		(arg)[i].dest_value = f_data[(int)arg[i].type](vm, proc, arg[i].value);
//		ft_printf("dest value = %d\n", (arg)[i].dest_value);
	}
}
