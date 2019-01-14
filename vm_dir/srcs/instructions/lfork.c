/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:09:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/10 17:10:10 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [lfork] instruction creates a new process at the address [arg 1], with the
** same state as the calling process excepted the PC (unless [arg 1] is 0),
** without the IDX_MOD distance restriction.
**
** Takes 1 argument: the address at which the new process must start.
*/

int		ins_lfork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	(void)vm;
	(void)proc;
	(void)arg;
	return (SUCCESS);
}
