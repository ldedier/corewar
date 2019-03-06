/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/06 14:27:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [st] instruction loads value from register [arg 1] to the arena at the
** address [arg 2] or the register #[arg 2].
**
** Takes 2 arguments : [arg 1] necessarily a REGISTER, [arg 2] either register
** or indirect.
*/

int		ins_st(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 1);
	getval_param_dest(vm, proc, &arg[1], 1);
	display_proc_ins(vm, proc);
	arg[1].value %= IDX_MOD;
	if (arg[1].type == T_REG)
	{
		proc->reg[arg[1].value - 1] = proc->reg[arg[0].value - 1];
		return (SUCCESS);
	}
	load_arena(vm, proc, proc->pc + arg[1].value, proc->reg[arg[0].value - 1]);
	return (SUCCESS);
}
