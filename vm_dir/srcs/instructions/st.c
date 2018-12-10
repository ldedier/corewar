/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 22:24:46 by emuckens         ###   ########.fr       */
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
	int		index;
	char	val;

//	ft_printf("arg first = %#x arg 2nd = %#x\n", arg[FIRST].value, arg[SECOND].value);
	index = arg[SECOND].value % IDX_MOD;
	val = getval(vm, &vm->proc[pl], arg[FIRST]);
//	ft_printf("index = %#x val = %#x\n", index, val); 
	vm->arena[(vm->proc[pl].pc + index + arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes) % MEM_SIZE] = val;
//	ft_printf("check arena index = %c\n", vm->arena[index]);
	loadval(vm, &vm->proc[pl], arg[FIRST], val);
	return (SUCCESS);
}
