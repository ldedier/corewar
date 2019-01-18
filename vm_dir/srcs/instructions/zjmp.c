/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:31 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/18 19:29:32 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [zjmp] instruction jumps PC to address [arg 1] if carry is ON (value = 1)
**
** Takes 1 argument: the address.
*/

int		ins_zjmp(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 1);
	if (proc->carry)
		proc->pending.pc = arg[0].dest_value;
	return (SUCCESS);
}
