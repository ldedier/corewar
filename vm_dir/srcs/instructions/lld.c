/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:30:07 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/18 19:30:08 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [lld] instruction loads the value from the first argument to the register
** from second argument, without the IDX_MOD distance restriction.
**
** Takes two arguments, the second one is necessarily a REGISTER
*/

int		ins_lld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 0);
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	proc->carry = !arg[0].dest_value;
	return (SUCCESS);
}
