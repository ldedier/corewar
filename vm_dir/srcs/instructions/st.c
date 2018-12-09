/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/09 21:18:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads.valueue from register # 1st arg to arena at 2nd arg address
** Input: vm (for arena and player), proc (for register and pc),
** arg for 2 args, 1st one necessarily a REGISTER
** Returns failure if i.valueid register, success otherwise
*/

int		ins_st(t_vm *vm, t_parameter arg[3], int pl)
{
(void)vm;
	int		index;
	int		val;

	index = arg[SECOND].value % IDX_MOD;
	val = getval(vm, &vm->proc[pl], arg[FIRST]);
	loadval(vm, &vm->proc[pl], arg[FIRST], val);
//	ft_memmove(vm->arena + vm->proc[pl].pc + (arg[SECOND].value % IDX_MOD),
//			vm->proc[pl].reg + arg[SECOND].value, REG_SIZE);
	return (SUCCESS);
}
