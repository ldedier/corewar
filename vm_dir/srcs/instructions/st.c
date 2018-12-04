/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 20:52:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from register # 1st arg to arena at 2nd arg address
** Input: vm (for arena and player), proc (for register and pc),
** arg for 2 args, 1st one necessarily a REGISTER
** Returns failure if invalid register, success otherwise
*/

int		ins_st(t_vm *vm, t_process *proc, t_arg arg[3])
{
	if (arg[FIRST].val >= REG_NUMBER)
		return (FAILURE); // verifier que c'est bien le cas
	ft_memmove(vm->arena + proc->pc + (arg[SECOND].val % IDX_MOD),
			proc->reg + arg[SECOND].val, REG_SIZE);
	return (SUCCESS);
}
