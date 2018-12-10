/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 18:40:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Input: vm (for arena and player), proc (for register and pc),
** arg for X args, 
** Returns 
*/

int		ins_lld(t_vm *vm, t_parameter arg[3], int pl)
{
	int	reg_ind;
	int	ar_ind;

	reg_ind = arg[SECOND].value;
	ar_ind = getval(vm, &vm->proc[pl], arg[FIRST]) + vm->proc[pl].pc;
	vm->proc[pl].reg[reg_ind] = vm->arena[ar_ind % MEM_SIZE];
	return (SUCCESS);
}

