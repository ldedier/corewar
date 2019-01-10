/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:18:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/10 17:18:43 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from arena at 2nd + 3rd arg->adress to register # 1st arg
** Input: vm (for arena and player), pl for process index,
** arg for 2 args, 1st one necessarily a REGISTER
*/

int		ins_sti(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int dest;

	getval_param_dest(vm, proc, &arg[0], 1);
	getval_param_dest(vm, proc, &arg[1], 1);
	getval_param_dest(vm, proc, &arg[2], 1);
	dest = proc->pc + (arg[1].dest_value + arg[2].dest_value) % IDX_MOD;
	proc->pending.dest = vm->arena;
	proc->pending.dest_index = dest;
	proc->pending.value = arg[0].dest_value;
	return (SUCCESS);
}
