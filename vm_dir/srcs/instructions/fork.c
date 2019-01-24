/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:28:28 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 12:14:14 by emuckens         ###   ########.fr       */
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
	static int	nb;

	if (!nb)
		nb = vm->nb_players + 1;
	t_process	*new_proc;
//	int			i;
	(void)arg;
//	(void)i;
	(void)new_proc;
	(void)vm;
	(void)proc;

	new_proc = (t_process *)ft_memalloc(sizeof(t_process));
	ft_memmove(new_proc, proc, sizeof(t_process));
//	arg[0].value = (unsigned short)arg[0].value % IDX_MOD;
//	ft_printf("FORK arg 0 value = %d, proc pc = %d\n", arg[0].value, proc->pc);
//	new_proc->player = proc->player;
	getval_param_dest(vm, proc, &arg[0], IDX_MOD);
	if (arg[0].value + proc->pc > IDX_MOD)
		arg[0].value -= IDX_MOD;
	new_proc->pc = (proc->pc + arg[0].value) % MEM_SIZE;
	new_proc->nb = nb;

	ft_bzero((void *)&new_proc->pending_ins, sizeof(t_instruction));

//	ft_printf(" (%d)\n", new_proc->pc);
//	new_proc->carry = proc->carry;
//	i = -1;
//	while (++i < 16) // deja le cas avec memmove
//		new_proc->reg[i] = proc->reg[i]; 
	if (ft_add_to_list_ptr(&vm->proc, (void *)new_proc, sizeof(t_process)))
		return (FAILURE);
	++nb;
	++proc->player->nb_proc;
//:w
//ft_printf("CREATE PROC | nb proc = %d\n", proc->player->nb_proc);
	return (SUCCESS);
}
