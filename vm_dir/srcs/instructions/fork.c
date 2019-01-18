/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:28 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/18 19:28:37 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [fork] instruction creates a new process at the address [arg 1], with the
** same state as the calling process excepted the PC obviously
** (unless [arg 1] is 0)
**
** Takes 1 argument: the address at which the new process must start.
*/

int		ins_fork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	t_process	*new_proc;
	int			i;

	new_proc = (t_process *)ft_memalloc(sizeof(t_process));
	new_proc->player = proc->player;
	new_proc->pc = (proc->pc + arg[0].value % IDX_MOD) % MEM_SIZE;
	new_proc->carry = proc->carry;
	i = -1;
	while (++i < 16)
		new_proc->reg[i] = proc->reg[i];
	if (ft_add_to_list_ptr(&vm->proc, (void *)new_proc, sizeof(t_process)))
		return (FAILURE);
	++proc->player->nb_proc;
	return (SUCCESS);
}
