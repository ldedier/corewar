/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 18:24:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** check for bitwise ^ between arg1 and arg2, store result in register # arg3
** Input: vm (for arena and player), proc (for register and pc),
** arg for 3 args, arg3 necessarily a REGISTER
*/

int		ins_xor(t_vm *vm, t_parameter arg[3], int pl)
{
	(void)vm;
	(void)pl;
	if (arg[THIRD].value >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	vm->proc[pl].reg[arg[THIRD].value] = arg[FIRST].value ^ arg[SECOND].value;
	return (SUCCESS);
}
