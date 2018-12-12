/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:32:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ins_live(t_vm *vm, t_parameter arg[3], int pl)
{
	t_process *proc;
	
	(void)pl;
	if (arg[FIRST].value >= MAX_PLAYERS)
		return (FAILURE);
	proc = get_proc_num(vm->proc, arg[FIRST].value);
	if (!proc->live)
		++vm->live.total_pl;
	proc->live = 1;
	proc->live = 1;
	vm->live.last_pl = arg[FIRST].value;
	++vm->live.nb;
	return (SUCCESS);
}
