/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/05 15:01:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

/*
** Checks conditions to resize cycle: more lives than NBR_LIVE or MAX_CHECKS
** ends of cycles since last resize
** Displays and sets variables accordingly
*/

static int		check_resize_cycle(t_vm *vm)
{
	if (vm->issued_live >= NBR_LIVE || !--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		return (1);
	}
	return (0);
}

/*
** Upon reaching cycle end, scans all players, checks if they have lived during
** previous turn. If so, sets live back to one; if not, remove from the list
** of all processes.
*/

static int		reset_live_allprocesses(t_vm *vm)
{
	t_list		*proc_lst;
	t_process	*proc;
	t_list		*tmp;

	proc_lst = vm->proc;
	while (proc_lst && (proc = ((t_process *)proc_lst->content)))
	{
		tmp = proc_lst->next;
		if (vm->total_cycle - proc->live_cycle >= vm->c_to_die)
		{
			if (kill_process(vm, &vm->proc, &proc_lst) == FAILURE)
				return (FAILURE);
		}
		else
		{
			proc->live = 0;
			proc->player->live = 0;
		}
		proc_lst = tmp;
	}
	vm->live = 0;
	return (SUCCESS);
}

/*
** Move pc of process in parameters
** In all cases except valid instruction (NB: meaning positive ins_bytelen) and
** zjmp instruction with carry on, move forward by absolute ins_bytelen value
** clear instruction and reset ins_bytelen
*/

static void		move_forward(t_vm *vm, t_process *proc)
{
	display_move(vm, proc);
	if (proc->ins_bytelen <= 0
			|| proc->pending_ins.op->opcode != ZJMP
			|| !proc->carry)
		proc->pc = mod(proc->pc + ft_abs(proc->ins_bytelen), MEM_SIZE);
	ft_bzero((t_instruction *)&proc->pending_ins, sizeof(t_instruction));
	proc->ins_bytelen = 0;
}

/*
** Finds action for process in parameters, for current cycle
** - if instruction pending, wait one cycle (exit function)
** - if pending instruction count is up: check again instruction data - if
** valid, execute action - and move forward
** - if no pending instruction, check if valid instruction at current pc
** - if no new valid instruction, move forward one
*/

static int		next_process_action(t_vm *vm, t_process *proc)
{
	t_instruction	*ins;
	int				op;
	static int		(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {&no_ins, &ins_live, &ins_ld, &ins_st,
			&ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
			&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
			&ins_aff};

	ins = &proc->pending_ins;
	if (--proc->ins_cycle > 1)
		return (SUCCESS);
	if (proc->ins_cycle == 1)
	{
		proc->ins_bytelen = get_ins(vm->arena, ins, proc->pc, 1);
		op = (proc->ins_bytelen > 0) * ins->op->opcode;
		if (f_ins[op](vm, proc, ins->params) == FAILURE)
			return (FAILURE);
		move_forward(vm, proc);
	}
	else if (get_ins(vm->arena, ins, proc->pc, 0))
		proc->ins_cycle = ins->op->nb_cycles;
	else if (++proc->pc == MEM_SIZE)
		proc->pc -= MEM_SIZE;
	return (SUCCESS);
}

/*
** Core of the game progression for one cycle :
** check next action for all processes
** if end of a cycle: check if resize and reset live for all processes
** NB: should be called until vm->proc empty
*/

int				play_one_cycle(t_vm *vm)
{
	t_list				*proc_lst;

	display_cycle(vm);
	proc_lst = vm->proc;
	while (proc_lst)
	{
		if (next_process_action(vm, (t_process *)proc_lst->content) == FAILURE)
			return (FAILURE);
		proc_lst = proc_lst->next;
	}
	if (vm->cycle >= vm->c_to_die)
	{
		if (reset_live_allprocesses(vm) == FAILURE)
			return (FAILURE);
		if (!(vm->cycle = 0) && check_resize_cycle(vm))
		{
			vm->c_to_die -= CYCLE_DELTA;
			display_resize(vm);
		}
		vm->issued_live = 0;
	}
	dump(vm);
	++vm->cycle;
	++vm->total_cycle;
	return (SUCCESS);
}
