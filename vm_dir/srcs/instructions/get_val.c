/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/08 16:07:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	getval_ind(t_vm *vm, t_process *proc, int index, int mod)
{
	int	val;
	(void)mod;

	(void)proc;
//	ft_printf("indirect | index = %d mod = %d\n", index, mod);
	val = getval_mod(vm->arena, index, DIR_SIZE, MEM_SIZE);
//	ft_printf("val = %d\n", val);
	return (val);
}

static int	getval_reg(t_vm *vm, t_process *proc, int index, int mod)
{
//	ft_printf("reg | index = %d\n", index);
	(void)vm;
	(void)mod;
	return (proc->reg[index - 1]);
}

static int	getval_dir(t_vm *vm, t_process *proc, int val, int mod)
{
//	ft_printf("direct\n");
	(void)vm;
	(void)proc;
	(void)mod;
	return (val);
}

void		getval_param_dest(t_vm *vm, t_process *proc, t_parameter *arg, int mod)
{
	static int (*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
			int index, int mod) = {NULL, &getval_reg, &getval_dir, &getval_ind};
//	int i;

//	i = -1;
//	while (++i < nb_params)
//	{
		arg->dest_value = f_data[(int)arg->type](vm, proc, arg->value, mod);
//		ft_printf("dest value = %d\n", (arg)[i].dest_value);
//	}
}
