/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/07 19:27:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from arena at 2nd + 3rd arg->adress to register # 1st arg
** Input: vm (for arena and player), pl for process index,
** arg for 2 args, 1st one necessarily a REGISTER
*/

int		ins_sti(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	(void)vm;
	(void)proc;
	(void)arg;
	int dest;

	getval_param_dest(vm, proc, &arg[0], 1);
	getval_param_dest(vm, proc, &arg[1], 1);
	getval_param_dest(vm, proc, &arg[2], 1);
	ft_printf("arg0 val = %d dest val = %d\n", arg[0].value, arg[0].dest_value);
	ft_printf("arg1 val = %d dest val = %d\n", arg[1].value, arg[1].dest_value);
	ft_printf("arg2 val = %d dest val = %d\n", arg[2].value, arg[2].dest_value);
	dest = (arg[1].value + arg[2].value) % IDX_MOD;
	vm->arena[dest % MEM_SIZE] = arg[0].value;
					return (SUCCESS);
	return (SUCCESS);
}
