/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:33:05 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** if carry is ON, jumps pc to arena at address arg1
** Input: vm (for arena and player), proc (for register and pc),
** arg for 1 arg
*/

int		ins_zjmp(t_vm *vm, t_parameter arg[3], int pl)
{
	t_process *proc;

	proc = get_proc_index(vm->proc, pl);
	if (proc->carry)
		proc->pc += (arg[FIRST].value % IDX_MOD);
	return (SUCCESS); // verifier si !carry = failure
}
