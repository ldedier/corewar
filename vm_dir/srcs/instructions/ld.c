/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/18 18:30:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads.value from arena at 1st arg adress to register # 2nd arg
** Input: vm (for arena and player), proc (for register and pc),
** arg->for 2 arg->, 2nd one necessarily a REGISTER
*/

int			ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int			val;

	val = arg[0].dest_value % IDX_MOD;

	ft_printf("val =  %d\n", val);
	loadval(vm, proc, &arg[1], val);
	ft_printf("val in reg 1 = %d\n", proc->reg[0]);
	ft_printf("val in reg 2 = %d\n", proc->reg[1]);
	ft_printf("val in reg 3 = %d\n", proc->reg[2]);
//	ft_printf("pc before ld = %d\n", vm->proc[pl].pc);
//	vm->proc[pl].pc += arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes;
//	ft_printf("pc after ld = %d\n", vm->proc[pl].pc);
	return (SUCCESS);
}

