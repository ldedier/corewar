/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 17:33:20 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Check conditions to resize cycle: more lives than NBR_LIVE or MAX_CHECKS
** ends of cycles since last resize
** display and set variables accordingly
*/

static void			check_resize_cycle(t_vm *vm, int *cycle)
{
	*cycle = 0;
	vm->live.nb = 0;
	if (vm->live.nb >= NBR_LIVE)
	{
		display(vm, 0, LIVES_TURN);
		display(vm, 0, NEW_RESIZE);
		vm->live.total_pl = 0;
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA;
		return ;
	}
	vm->live.total_pl = 0;
	display(vm, 0, AUTO_RESIZE);
	if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA;
		display(vm, 0, NEW_RESIZE);
	}
}

/*
** Upon reaching cycle end
** Scans all players, checks if they have lived previous turn;
** if so set live back to one, if not remove from process list;
*/

static void		reset_live_allprocesses(t_vm *vm)
{
	int			i;
	t_list		*players;
	t_process	*proc;
	t_list		*tmp;

	display(vm, 0, CYCLE_END);
	players = vm->proc;
	i = vm->nb_players;
	while (players && (proc = ((t_process *)players->content)))
	{
		tmp = players;
		if (!proc->live && vm->nb_players > 1)
		{
			display(vm, proc, PL_DEATH);
			players = players->next;
			vm->proc = (tmp == vm->proc) ? tmp->next : vm->proc;
			ft_memdel((void **)&tmp->content);
			ft_memdel((void **)&tmp);
			--vm->nb_players;
		}
		else if ((proc->live = 1))
		{
			vm->live.last_pl = proc;
			players = players->next;
		}
	}
}

/*
** Checks if latest instruction is still ongoing (via proc->cycle) and display
*/

static int		last_instruction_unresolved(t_vm *vm, t_process *proc)
{
	if (proc->cycle > 0 && ft_printf("%*s", PAD_INS, ""))
	{
		display(vm, proc, PL_CYCLE);
		--proc->cycle;
		return (1);
	}
	return (0);
}

/*
** checks if last instruction is still running
** else, if there's a  valid instruction at current position launch it,
** adjust cycles, and display
** else move on
*/

static int		launch_instruction(t_vm *vm, t_process *proc)
{
	t_instruction	ins;
//	int				ret;
	static int		(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};

	if (last_instruction_unresolved(vm, proc))
		return (0);
	if ((proc->ins_cycle = get_instruction(vm->arena,
					&ins, proc->pc, MEM_SIZE)))
	{
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
		proc->cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		display_ins_description(vm, ins.op.description, ins.op.opcode);
		display(vm, proc, PL_CYCLE);
		--proc->cycle;
		return (1);
	}
	proc->ins_cycle = 1;
	display(vm, proc, MOVE_ONE);
	display(vm, proc, PL_PC);
	return (0);
}

/*
** If there's only 1 player or cycle_to_die = 0, displays winner and exits game,
** else checks if cycle_to_die should change value
*/

int			handle_end_cycle(t_vm *vm, int *cycle)
{
	reset_live_allprocesses(vm);
	if (vm->nb_players <= 1 || !vm->c_to_die)
	{
		display(vm, get_proc_num(vm->proc, vm->live.last_pl->player->num),
				PL_VICTORY);
		return (0);
	}
	check_resize_cycle(vm, cycle);
	return (1);
}

/*
**process_cycle
*/

void		process_cycle(t_vm *vm)
{
	t_list				*players;
	t_process			*proc;
	int					change;

	players = vm->proc;
	change = 0;
	while (players)
	{
		proc = ((t_process *)(players->content));
		display(vm, proc, TURN_PLAYER);
		if (!proc->cycle)
		{
			proc->pc = (proc->pc + proc->ins_cycle) % MEM_SIZE;
			display_register(proc);
			ft_printf("\n");
		}
		if (launch_instruction(vm, proc))
			change = 1;
		if (!vm->visu.active)
			ft_printf("\n");
		if (!players->next && change)
			display_arena((unsigned char *)vm->arena);
		players = players->next;
	}
}

/*
** Core of the game progression : continues until cycles to end = 0 or
** only 1 player left.
** Each turn, it :
** Checks if it's the end of a cycle
** Loops through all players:
**	- moves forward according to latest instruction or 1 if no valid instruction
**	- checks if there's a valid instruction
*/

int		play(t_vm *vm)
{
	static int cycle;

	cycle = 1;
	display(vm, 0, CYCLE_NBR);
	while (!(cycle == vm->c_to_die && !handle_end_cycle(vm, &cycle)))
	{
		ft_printf("\n%scycle = %d | %s ", COLF_BGREY,
				cycle, MSG_CYCLES_REMAINING);
		ft_printf(" [ %d ] %s\n", CYCLE_TO_DIE - cycle, COLF_OFF);
		process_cycle(vm);
		++cycle;
	}
	return (0);
}
