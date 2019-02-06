/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:08:06 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/06 16:07:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [ld] instruction loads the value from the first argument to the register
** from second argument.
**
** Takes two arguments, the second one is necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3])
{

	display_proc_ins(vm, proc); 
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	proc->reg[arg[1].value - 1] = arg[0].dest_value;
	proc->carry = !arg[0].dest_value;
	return (SUCCESS);
}
