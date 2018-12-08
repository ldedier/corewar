/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 14:47:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads.valueue from arena at 1st arg adress to register # 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg for 2 args, 2nd one necessarily a REGISTER
** Returns failure if invalid register, success otherwise
*/

int		ins_ld(t_vm *vm, t_parameter arg[3], int pl)
{
	(void)vm;
	if (arg[SECOND].value >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	ft_memmove(vm->proc[pl].reg + arg[SECOND].value,
			vm->arena + vm->proc[pl].pc + (arg[FIRST].value % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
