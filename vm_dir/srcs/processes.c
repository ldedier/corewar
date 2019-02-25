/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:24:20 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/25 17:43:54 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_processes function initializes each player's starting process.
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
 ** Copy significant process data to newly created process
 */
void	copy_process_stat(t_process **proc, t_process *src)
{
	(*proc)->player = src->player;
	(*proc)->ins_bytelen = src->ins_bytelen;
	(*proc)->live_cycle = src->live_cycle;
	ft_memmove((*proc)->reg, src->reg, REG_NUMBER * sizeof(int));
	(*proc)->pc = src->pc;
	(*proc)->pending_ins.op = NULL;
	(*proc)->pending_ins.params[0].nb_bytes = 0;
	(*proc)->pending_ins.params[1].nb_bytes = 0;
	(*proc)->pending_ins.params[2].nb_bytes = 0;
	(*proc)->carry = src->carry;
	(*proc)->cycle = src->cycle;
	(*proc)->ins_cycle = src->ins_cycle;
	(*proc)->live = 0;
	++(*proc)->player->nb_proc;
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
		copy_process_stat(&process, src);
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
