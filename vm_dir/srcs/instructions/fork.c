/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/07 19:23:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [fork] instruction creates a new process at the address [arg 1], with the
** same state as the calling process excepted the PC (unless [arg 1] is 0)
**
** Takes 1 argument: the address at which the new process must start.
*/

int		ins_fork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	(void)vm;
	(void)proc;
	(void)arg;
	++proc->player->nb_proc;
	return (SUCCESS);
}
