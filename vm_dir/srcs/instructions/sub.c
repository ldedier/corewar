/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 18:23:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Add value from registers # arg1 and # arg2, store in register #3
** Input: vm (for arena and player), proc (for register and pc),
** arg: for 3 arg, all necessarily REGISTERS
** Returns failure if i.valueid register, success otherwise
*/

int		ins_sub(t_vm *vm, t_parameter arg[3], int pl)
{
	int	sub;

	(void)vm;
	(void)pl;
//	if (arg[FIRST]->value >= REG_NUMBER
//			|| arg[SECOND]->value >= REG_NUMBER
//			|| arg[THIRD]->value >= REG_NUMBER)
//		return (FAILURE); // verifier que c'est bien le cas
	sub = vm->proc[pl].reg[arg[FIRST].value] - vm->proc[pl].reg[arg[SECOND].value]; // verifier que la soustraction est bien dans ce sens
	vm->proc[pl].reg[arg[THIRD].value] = sub;
	return (SUCCESS);
}
