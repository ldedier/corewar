/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 11:45:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from register # 1st arg to arena at 2nd arg address
** Input: vm (for arena and player), proc (for register and pc),
** arg : for 2 arg, 1st one necessarily a REGISTER
*/

int		ins_st(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	getval_param_dest(vm, proc, &arg[0], 1);
	getval_param_dest(vm, proc, &arg[1], IDX_MOD);
	ft_printf("in st, arg0 val = %d dest value = %d arg1 val = %d destval = %d\n", arg[0].value, arg[0].dest_value, arg[1].value, arg[1].dest_value);
	ft_printf("reg1 = %d\n", proc->reg[0]);
	ft_printf("reg2 = %d\n", proc->reg[1]);
	ft_printf("reg3 = %d\n", proc->reg[2]);
//	val = arg[0].dest_value % IDX_MOD;
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	return (SUCCESS);
}
