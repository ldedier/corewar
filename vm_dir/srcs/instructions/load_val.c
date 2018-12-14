/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 21:34:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		load_arena(t_vm *vm, t_process *proc, int index, int val)
{
	(void)proc;
	ft_memmove((void *)(vm->arena + index), (void *)&val, IND_SIZE); 
//	vm->arena[index - 1] = val;
}

static void		load_reg(t_vm *vm, t_process *proc, int index, int val)
{
	(void)vm;
	//penser a load en meme temps dans vm->metarena pour la couleur
	//
	ft_memmove((void *)(proc->reg + index - 1), (void *)&val, REG_SIZE); 
//	ft_printf("new in reg = %d\n", proc->reg[index - 1]);
//	proc->reg[index - 1] = val;
}

void		loadval(t_vm *vm, t_process *proc, t_parameter arg, int val)
{
	static void	(*f_data[NB_TYPES + 1])(t_vm *vm, t_process *proc,
				int index, int val) = {NULL, &load_reg, &load_arena, &load_arena};
	f_data[(int)arg.type](vm, proc, arg.value, val);
}


