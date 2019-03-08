/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:24:20 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/07 18:59:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		kill_adjust_ptr(t_list **proc_lst, t_list **proc)
{
	t_list *tmp;

	if (*proc == *proc_lst)
	{
		*proc_lst = (*proc_lst)->next;
		return ;
	}
	tmp = *proc_lst;
	while (tmp && tmp->next && tmp->next != *proc)
		tmp = tmp->next;
	tmp->next = (*proc)->next;
}

int				kill_process(t_vm *vm, t_list **proc_lst, t_list **proc)
{
	t_process *process;

	process = (t_process *)(*proc)->content;
	(void)proc_lst;
	vm->metarena[process->pc].process_color = -1;
	vm->metarena[process->pc].death_color = process->player->color.value;
	vm->metarena[process->pc].death_fade = MAX_FADE;
	--process->player->nb_proc;
	kill_adjust_ptr(&vm->proc, proc);
	display_last_live(vm, process);
	ft_memdel((void **)&(*proc)->content);
	ft_memdel((void **)proc);
	return (SUCCESS);
}

/*
** initializes each player's initial process.
*/

int				init_processes(t_vm *vm)
{
	int		i;
	int		index;
	int		start;

	i = -1;
	index = 1;
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant
			&& ++index
			&& !add_process(vm, i, start, NULL))
			return (0);
		vm->player[i].nb_proc = 1;
		if (vm->player[i].relevant)
			vm->winner = ((t_process *)(vm->proc->content))->player;
	}
	return (1);
}

/*
** Copy significant process data to newly created process (copy of creator)
*/

void			copy_process_stat(t_process *proc, t_process *src)
{
	proc->player = src->player;
	proc->ins_bytelen = src->ins_bytelen;
	proc->live_cycle = src->live_cycle;
	ft_memmove(proc->reg, src->reg, sizeof(proc->reg));
	proc->pc = src->pc;
	proc->pending_ins.op = NULL;
	proc->pending_ins.params[0].nb_bytes = 0;
	proc->pending_ins.params[1].nb_bytes = 0;
	proc->pending_ins.params[2].nb_bytes = 0;
	proc->carry = src->carry;
	proc->cycle = src->cycle;
	proc->ins_cycle = src->ins_cycle;
	proc->live = 0;
	++proc->player->nb_proc;
}

/*
** add_process function is used by init_processes to add a process to the list
*/

t_list			*add_process(t_vm *vm, int index, int start, t_process *src)
{
	t_process	*process;
	static int	nb;

	if (!(process = (t_process *)ft_memalloc(sizeof(t_process))))
		return (NULL);
	if (src)
	{
		copy_process_stat(process, src);
	}
	else
	{
		process->player = &vm->player[index];
		process->pc = start;
		vm->metarena[start].process_color = process->player->color.value;
		process->reg[0] = process->player->num;
	}
	process->nb = ++nb;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}
