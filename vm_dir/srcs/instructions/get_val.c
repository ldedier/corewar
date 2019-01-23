/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:00:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/23 21:27:12 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static long	getval_ind(t_vm *vm, t_process *proc, int *index, int modulo)
{
	int	val;

	(void)proc;
	(void)modulo;
//	int		valarena;
//	if (mod == IDX_MOD)
//		index %= mod;
//	ft_printf("getval ind, IDX MOD = %d\n", IDX_MOD);
	*index = mod(*index, IDX_MOD);
	ft_printf("index = %d\n", *index);
	val = getval_mod(vm->arena, *index, DIR_SIZE, MEM_SIZE);
	ft_printf("1 getval ind, val = %d\n", val);
//	val = mod(val, MEM_SIZE);
//	ft_printf("2 getval ind, val = %d\n", val);
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

	ft_printf("arg type= %d\n", arg->type);
	ft_printf("before arg.value = %d\n", arg->value);
	arg->dest_value = f_data[(int)arg->type](vm, proc, &arg->value, modulo);
	arg->dest_value = mod(arg->dest_value, modulo);
//	ft_printf("after, arg value = %d arg dest value = %d\n", arg->value, arg->dest_value);
}
