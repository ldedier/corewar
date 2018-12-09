/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/09 20:56:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads.valueue from arena at 1st arg adress to register # 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg for 2 args, 2nd one necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_parameter arg[3], int pl)
{
	int	reg_ind;
	int	ar_ind;

	reg_ind = arg[SECOND].value;
	ar_ind = getval(vm, &vm->proc[pl], arg[FIRST]) % IDX_MOD + vm->proc[pl].pc;
	ar_ind = ar_ind % MEM_SIZE - 1;
	vm->proc[pl].reg[reg_ind] = vm->arena[ar_ind];
	return (SUCCESS);
}
