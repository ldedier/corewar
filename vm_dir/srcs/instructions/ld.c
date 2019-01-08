/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/08 16:49:21 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from first argument to register given by 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg for the 2 arguments, the second one is necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	proc->carry = !arg[0].dest_value;
	return (SUCCESS);
}
