/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:09:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/28 18:40:23 by emuckens         ###   ########.fr       */
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
	t_process	*new_proc;
	int			i;
	(void)proc;
	(void)vm;
	(void)arg;
	(void)i;
	(void)new_proc;

	ft_printf("LFORK\n");
	add_process(vm, 0, 0, proc);
//	new_proc = (t_process *)ft_memalloc(sizeof(t_process));
//	new_proc->player = proc->player;
//	new_proc->pc = (proc->pc + arg[0].value) % MEM_SIZE;
//	new_proc->carry = proc->carry;
	getval_param_dest(vm, proc, &arg[0], arg[0].value);
	arg[0].retrieval_mode = 0;
	((t_process *)vm->proc->content)->pc = mod(proc->pc + arg[0].value, MEM_SIZE);
	i = -1;
	arg[0].retrieval_mode = 0;
//	while (++i < 16)
//		new_proc->reg[i] = proc->reg[i];
//	if (ft_add_to_list_ptr(&vm->proc, (void *)new_proc, sizeof(t_process)))
//		return (FAILURE);
//	++proc->player->nb_proc;
	display_proc_ins(vm, proc);
	if (!vm->visu.active && vm->display & (1 << MSG_INS))
		ft_printf(" (%d)", ((t_process *)vm->proc->content)->pc);
	return (SUCCESS);
}
