/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 15:19:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** if carry is ON, jumps pc to arena at address arg1
** Input: vm (for arena and player), proc (for register and pc),
** arg for 1 arg
** Returns failure if i.valueid register, success otherwise
*/

int		ins_zjmp(t_vm *vm, t_parameter arg[3], int pl)
{
	(void)vm;
	if (vm->proc[pl].carry)
		vm->proc[pl].pc += (arg[FIRST].value % IDX_MOD);
	return (SUCCESS); // verifier si !carry = failure
}
