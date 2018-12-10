/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 18:35:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Loads value from arena at 2nd + 3rd arg->adress to register # 1st arg
** Input: vm (for arena and player), pl for process index,
** arg for 2 args, 1st one necessarily a REGISTER
*/

int		ins_sti(t_vm *vm,  t_parameter arg[3], int pl)
{
	int sum;

	sum = getval(vm, &vm->proc[pl], arg[SECOND]);
	sum += getval(vm, &vm->proc[pl], arg[THIRD]);
//	ft_printf("sti, sum = %d\n", sum);
	vm->proc[pl].reg[arg[FIRST].value - 1] = vm->arena[sum % MEM_SIZE];
	return (SUCCESS);
}
