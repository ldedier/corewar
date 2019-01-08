/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/08 16:01:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** if carry is ON, jumps pc to arena at address # arg 1
** Input: vm (for arena and player), proc (for register and pc),
** arg for 1 arg
*/

int		ins_zjmp(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 1);
	ft_printf("dest val = %d dest val mod idxmod = %d pc = %d\n", arg[0].dest_value % MEM_SIZE, arg[0].dest_value % IDX_MOD, proc->pc);
	if (proc->carry)
	{
		proc->pending.pc = (arg[0].dest_value);
	}
	return (SUCCESS); // verifier si !carry = failure
}
