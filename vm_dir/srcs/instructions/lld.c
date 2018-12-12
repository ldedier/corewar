/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:34:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Input: vm (for arena and player), proc (for register and pc),
** arg for X args, 
** Returns 
*/

int		ins_lld(t_vm *vm, t_parameter arg[3], int pl)
{
	int	reg_ind;
	int	ar_ind;
	t_process *proc;

	proc = get_proc_index(vm->proc, pl);
	reg_ind = arg[SECOND].value;
	ar_ind = getval(vm, proc, arg[FIRST]) + proc->pc;
	proc->reg[reg_ind] = vm->arena[ar_ind % MEM_SIZE];
	return (SUCCESS);
}

