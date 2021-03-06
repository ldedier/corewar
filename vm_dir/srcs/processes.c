/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:24:20 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/11 15:07:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				kill_process_at_head(t_vm *vm)
{
	t_list *tmp;

	while ((tmp = vm->proc) && (t_process *)tmp->content && vm->total_cycle
			- ((t_process *)tmp->content)->live_cycle >= vm->c_to_die)
	{
		vm->proc = vm->proc->next;
		if (kill_process(vm, &tmp) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int				kill_process(t_vm *vm, t_list **proc)
{
	t_fade	*killed;

	if (vm->visu.active)
	{
		if (!(killed = (t_fade *)ft_memalloc(sizeof(t_fade))))
			return (error_exit_msg(vm, ERR_MALLOC));
		killed->pc = ((t_process *)(*proc)->content)->pc;
		killed->color = ((t_process *)(*proc)->content)->player->color.value;
		killed->value = MAX_FADE;
		if (ft_add_to_list_ptr(&vm->killed_proc, (void *)killed,
					sizeof(t_fade)))
			return (error_exit_msg(vm, ERR_MALLOC));
	}
	--((t_process *)(*proc)->content)->player->nb_proc;
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
	if (!vm->nb_players)
		return (error_exit_msg(vm, NO_PLAYER));
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant
			&& ++index
			&& !add_process(vm, i, start, NULL))
		{
			return (error_exit_msg(vm, ERR_MALLOC));
		}
		if (vm->player[i].relevant)
		{
			vm->player[i].nb_proc = 1;
			vm->winner = ((t_process *)(vm->proc->content))->player;
		}
	}
	return (SUCCESS);
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
		process->reg[0] = process->player->num;
	}
	process->nb = ++nb;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}
