/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/05 16:08:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ins_live(t_vm *vm, t_process *proc, t_arg arg[3])
{
	(void)proc;
	if (arg[FIRST].val >= MAX_PLAYERS)
		return (FAILURE);
	// rajouter l'activation du marqueur live, voir avec usama s'il en a deja un
	proc->live = 1;
	ft_printf("Player %s lives !!\n", vm->player[arg[FIRST].val].name);
	return (SUCCESS);
}
