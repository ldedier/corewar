/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 20:49:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from arena at 1st arg adress to register # 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg for 2 args, 2nd one necessarily a REGISTER
** Returns failure if invalid register, success otherwise
*/

int		ins_sti(t_vm *vm, t_process *proc, t_arg arg[3])
{
	int sum;
	if (arg[THIRD].nb_bytes != T_IND || arg[SECOND].nb_bytes != T_IND)
		return (FAILURE); // verifier que c'est bien le cas
	sum = arg[SECOND].val + arg[FIRST].val; // verifier si verification taille en amont?
	ft_memmove(proc->reg + arg[THIRD].val, vm->arena + proc->pc + (sum % IDX_MOD), REG_SIZE);
	return (SUCCESS);
}
