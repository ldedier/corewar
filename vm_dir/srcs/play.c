/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/22 19:07:04 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Checks conditions to resize cycle: more lives than NBR_LIVE or MAX_CHECKS
** ends of cycles since last resize
** Displays and sets variables accordingly
*/

static int			check_resize_cycle(t_vm *vm, int *cycle)
{
	(void)cycle;

	if (vm->issued_live >= NBR_LIVE)
		vm->checks = MAX_CHECKS;
	else if (!--vm->checks)
		vm->checks = MAX_CHECKS;
	else
		return (0);
	return (1);
}

static void		kill_adjust_ptr(t_list **proc_lst, t_list **proc)
{
	t_list *tmp;

	if (*proc ==  *proc_lst)
	{
		*proc_lst = (*proc_lst)->next;
		return ;
	}
	tmp = *proc_lst;
	while (tmp && (tmp)->next && (tmp)->next != *proc)
			tmp = (tmp)->next;
	(tmp)->next = (*proc)->next;
}

int		list_size(t_vm *vm, t_list *l)
{
	t_list *tmp;
	int		i;

	(void)vm;
	tmp = l;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++i;
	}
	return (i);
}


static int		kill_process(t_vm *vm, t_list **proc_lst, t_list **proc)
{
	t_fade	*killed_proc;
	(void)*proc_lst;

	killed_proc = (t_fade *)ft_memalloc(sizeof(t_fade));
	killed_proc->pc = ((t_process *)(*proc)->content)->pc;
	killed_proc->color =
					*((int *)((t_process *)(*proc)->content)->player->color.value);
	killed_proc->value = MAX_FADE;
	--((t_process *)(*proc)->content)->player->nb_proc;
	if (ft_add_to_list_ptr(&vm->killed_proc,
										(void *)killed_proc, sizeof(t_fade)))
		return (-1);
		kill_adjust_ptr(&vm->proc, proc);
		display_last_live(vm, (t_process *)(*proc)->content);

	ft_memdel((void **)&(*proc)->content);
	ft_memdel((void **)proc);
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
			kill_process(vm, &vm->proc, &proc_lst);
		}
		else
		{
			proc->live = 0;
			proc->player->live = 0;
		}
			proc_lst = tmp;
	}
	vm->live = 0;
	vm->issued_live = 0;
	return (0);
}

/*
** Checks if last instruction is still running.
** Else, if there's a valid instruction at the current position, launches it,
** adjusts cycles, and displays. If not, moves on.
*/

static int		launch_instruction(t_vm *vm, t_process *proc)
{
	static int	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};
	t_instruction	*ins;

	ins = &proc->pending_ins;
	if (--proc->ins_cycle > 1)
		return (0);
	if (proc->ins_cycle == 1)
	{
//		if (proc->nb == 118)
//			ft_printf("proc carry = %d op = %d\n", proc->carry, ins->op->opcode);
		proc->ins_bytelen = get_instruction(vm->arena, ins, proc->pc, MEM_SIZE);
//		if (ins->op->opcode == LIVE)
//			ft_printf("bytlen = %d\n", proc->ins_bytelen);
		if (proc->ins_bytelen > 0/* && ins->op->opcode == *(vm->arena + proc->pc)*/)
		{
//			proc->carry = 0;
//			ft_printf("opcode = %d arena val = %d\n", ins->op->opcode, *(unsigned char *)(vm->arena + proc->pc));
				f_ins[ins->op->opcode](vm, proc, ins->params);
			display_move(vm, proc);
			if (ins->op->opcode != ZJMP || !proc->carry)
				proc->pc = mod(proc->pc + proc->ins_bytelen, MEM_SIZE);
		}
		else
		{
//			if (ins->op->carry)
//				proc->carry = 0;
//			ft_printf("P  %d abandoned action = %d\n", proc->nb, ins->op->opcode);
			display_move(vm, proc);
			proc->pc = mod(proc->pc - proc->ins_bytelen, MEM_SIZE);
		}
		ins->op = NULL;
		ins->params[0].nb_bytes = 0;
		ins->params[1].nb_bytes = 0;
		ins->params[2].nb_bytes = 0;
		proc->ins_bytelen = 0;
		return (0);

	}
	else if (!(proc->ins_bytelen = get_instruction(vm->arena, ins, proc->pc, MEM_SIZE)))
	{
			if (++proc->pc == MEM_SIZE)
				proc->pc -= MEM_SIZE;
	}
	else
		proc->ins_cycle = ins->op->nb_cycles;
	return (0);
}

/*
** Core of the game progression for one turn :
** Checks if it's the end of a cycle
** Loops through all players:
**	- moves forward according to latest instruction or 1 if no valid instruction
**	- checks if there's a valid instruction
** NB: should be called until vm->proc empty
*/

void			process_cycle(t_vm *vm)
{
	t_list				*proc_lst;
	t_process			*proc;
	int					new_ctodie;

	display_cycle(vm);
	proc_lst = vm->proc;
	while (proc_lst)
	{
		proc = (t_process *)proc_lst->content;
		launch_instruction(vm, proc);
		proc_lst = proc_lst->next;
	}
	if (vm->cycle >= vm->c_to_die)
	{
		new_ctodie = check_resize_cycle(vm, &vm->cycle);
		reset_live_allprocesses(vm);
		if (new_ctodie)
		{
			vm->c_to_die -= CYCLE_DELTA;
			display_resize(vm);
		}
		vm->cycle = 0;
	}
	++vm->cycle;
	++vm->total_cycle;
}

/*
** Generates and runs through game for 2 players, to communicate result to
** server for one-on-one match and subsequent score computation
*/

int		fight_cores(t_vm *vm, t_player *pl1, t_player *pl2)
{
	clear_vm(vm);
	ft_memmove(&vm->player[0], pl1, sizeof(t_player));
	ft_memmove(&vm->player[1], pl2, sizeof(t_player));
	vm->player[0].num = 1; //faire par pointeurs...
	vm->player[1].num = 2;
	vm->player[0].relevant = 1;
	vm->player[1].relevant = 1;
	vm->player[2].relevant = 0;
	vm->player[3].relevant = 0;
	dispatch_players_init(vm);
	if (!init_processes(vm))
		error_exit_msg(INIT_PROC_ERROR);
	while (vm->proc)
	{
		process_cycle(vm);
	}
	if (vm->winner == &vm->player[0])
		vm->winner = pl1;
	else
		vm->winner = pl2;
	vm->visu.active = 0;
	return (0);
}
