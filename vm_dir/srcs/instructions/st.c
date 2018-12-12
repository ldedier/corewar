/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 20:56:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from register # 1st arg to arena at 2nd arg address
** Input: vm (for arena and player), proc (for register and pc),
** arg : for 2 arg, 1st one necessarily a REGISTER
*/

int		ins_st(t_vm *vm, t_parameter arg[3], int pl)
{
	int			index;
	char		val;
	int			i;
	t_process	*proc;

	proc = get_proc_num(vm->proc, pl);
	index = arg[SECOND].value % IDX_MOD;
	val = getval(vm, proc, arg[FIRST]);
	i = arg[SECOND].nb_bytes;
	while (i)
	{
		vm->arena[(index + i) % MEM_SIZE] = (val & 255); 
//		ft_printf("val = %d arena = %#x\n", val, vm->arena[vm->proc[pl].pc + index + i]);
		val = val >> 8;
		--i;
	}
//	loadval(vm, &vm->proc[pl], arg[FIRST], val);
	return (SUCCESS);
}
