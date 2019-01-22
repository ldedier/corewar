/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:29:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/22 19:10:46 by emuckens         ###   ########.fr       */
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
	arg[1].value %= IDX_MOD;
//	ft_printf("val 0 = %d arg[0] dest val = %d val 1 = %d arg 1 dest value = %d\n", arg[0].value, arg[0].dest_value, arg[1].value, arg[1].dest_value);
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	return (SUCCESS);
}
