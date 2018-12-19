/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 15:16:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads.value from arena at 1st arg adress to register # 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg->for 2 arg->, 2nd one necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	proc->carry = !arg[0].dest_value;
	return (SUCCESS);
}

