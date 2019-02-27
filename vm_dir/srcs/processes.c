/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:24:20 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/27 18:01:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		kill_adjust_ptr(t_list **proc_lst, t_list **proc)
{
	t_list *tmp;

	if (*proc ==  *proc_lst)
	{
		*proc_lst = (*proc_lst)->next;
		return ;
	}
	tmp = *proc_lst;
	while (tmp && tmp->next && tmp->next != *proc)
		tmp = tmp->next;
	tmp->next = (*proc)->next;
}

int		kill_process(t_vm *vm, t_list **proc_lst, t_list **proc)
{
	t_fade	*killed_proc;
	(void)*proc_lst;

	if (!(killed_proc = (t_fade *)ft_memalloc(sizeof(t_fade))))
		return (error_exit_msg(vm, ERR_MALLOC));
	killed_proc->pc = ((t_process *)(*proc)->content)->pc;
	killed_proc->color = ((t_process *)(*proc)->content)->player->color.value;
	killed_proc->value = MAX_FADE;
	--((t_process *)(*proc)->content)->player->nb_proc;
	if (ft_add_to_list_ptr(&vm->killed_proc,
				(void *)killed_proc, sizeof(t_fade)))
		return (error_exit_msg(vm, ERR_MALLOC));
	kill_adjust_ptr(&vm->proc, proc);
	display_last_live(vm, (t_process *)(*proc)->content);
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
		if (vm->player[i].relevant && ++index && !add_process(vm, i, start, NULL))
			return (0);
		vm->player[i].nb_proc = 1;
		vm->winner = ((t_process *)(vm->proc->content))->player;
	}
	return (1);
}

/*
** Copy significant process data to newly created process (copy of creator)
*/

void	copy_process_stat(t_process * proc, t_process *src)
{
	proc->player = src->player;
	proc->ins_bytelen = src->ins_bytelen;
	proc->live_cycle = src->live_cycle;
	ft_memmove(proc->reg, src->reg, REG_NUMBER * sizeof(int));
	proc->pc = src->pc;
	proc->carry = src->carry;
	proc->cycle = src->cycle;
	proc->ins_cycle = src->ins_cycle;
	++proc->player->nb_proc;
}

/*
** add_process function is used by init_processes to add a process to the list
*/

t_list			*add_process(t_vm *vm, int index, int start, t_process *src)
{
	t_process	*process;
	static int	nb = 0;

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
		process->reg[0] = process->player->num;
	}
	process->nb = ++nb;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}
