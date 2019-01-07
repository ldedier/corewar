/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/07 17:35:39 by emuckens         ###   ########.fr       */
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
	(void)cycle;
	if (vm->live >= NBR_LIVE)
	{
//		display(vm, NULL, LIVES_TURN);
//		display(vm, NULL, NEW_RESIZE);
		vm->checks = MAX_CHECKS ;
		vm->c_to_die -= CYCLE_DELTA;
		return;
	}
//	display(vm, NULL, AUTO_RESIZE);
	if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA;
//		ft_printf("new cycle to die = %d\n", vm->c_to_die);
		display(vm, NULL, NEW_RESIZE);
	}
}

/*
** Upon reaching cycle end
** Scan all players, checks if they have lived previous turn;
** if so set live back to one, if not remove from process list;
*/

static void		reset_live_allprocesses(t_vm *vm)
{
	t_list		*proc_lst;
	t_list		*tmp;
	t_process *proc;

	display(vm, NULL, CYCLE_END);
	proc_lst = vm->proc;
	while (proc_lst && (proc = ((t_process *)proc_lst->content)))
	{
		tmp = proc_lst;
		if (!proc->live)
		{
//			ft_printf("PROCESS DEAD\n");
			display(vm, proc, PL_DEATH);
			proc_lst = proc_lst->next;
			vm->proc = (tmp == vm->proc) ? tmp->next : vm->proc;
			ft_memdel((void **)&tmp->content);
			ft_memdel((void **)&tmp);
		}
		else 
		{
//			ft_printf("PROCESS ALIVE\n");
			vm->winner = proc->player;
			proc_lst = proc_lst->next;
		}
		proc->live = 0;
	}
}

/*
** Checks if latest instruction is still ongoing (via proc->cycle) and display
*/

static int		last_instruction_unresolved(t_vm *vm, t_process *proc)
{
	(void)vm;
	if (proc->cycle > 0 && ft_printf("%*s", PAD_INS, ""))
	{
//		display(vm, proc, PL_CYCLE);
		--proc->cycle;
		return (1);
	}
//	ft_printf("last instruction resolved! current pc = %d ins bytelen = %d\n", proc->pc, proc->ins_bytelen);
	return (0);
}

/*
** check if last instruction still running
** else, if valid instruction at current position, launch it, adjust cycles, and display
** else move on
*/

static int		launch_instruction(t_vm *vm, t_process *proc)
{
	t_instruction	ins;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc, 
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};

	if (last_instruction_unresolved(vm, proc))
		return (0);
//	ft_printf("ins bytelen = %d\n", proc->ins_bytelen);
	if ((proc->ins_bytelen = get_instruction(vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
//		ft_printf("new ins cycle = %d\n", proc->ins_bytelen);
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
		proc->cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		display_ins_description(vm, ins.op.description, ins.op.opcode);
//		display(vm, proc, PL_CYCLE);
		--proc->cycle; 
		return (1);
	}
	proc->ins_bytelen = 1;
	display(vm, proc, MOVE_ONE);
	display(vm, proc, PL_PC);
	return (0);
}

/*
** if 1 player or cycle_to_die = 0, display winner and return 0 to exit game
** else check if cycle_to_die should change value
*/

int			handle_end_cycle(t_vm *vm, int *cycle)
{
//	t_player *player;

	if (*cycle < vm->c_to_die)
		return (0);
	reset_live_allprocesses(vm);
//	player = get_player_num(vm->proc, vm->live.winner->num);
	if (!vm->proc)
	{
		display(vm, NULL, PL_VICTORY);
		return (1);
	}
	*cycle = 0;
	check_resize_cycle(vm, cycle);
	return (0);
}

/*
**
*/

void		process_cycle(t_vm *vm)
{
	t_list				*proc_lst;
	t_process			*proc;
//	int					change; // a supprimer avec l'affichage de l'arene

	proc_lst = vm->proc;
//	change = 0; // idem;
	while (proc_lst)
	{
		proc = ((t_process *)(proc_lst->content));
		display(vm, proc, TURN_PLAYER);
		if (!proc->cycle)
		{
			proc->pc = (proc->pc + proc->ins_bytelen) % MEM_SIZE;
			display_register(proc);
			ft_printf("\n");
		}
		launch_instruction(vm, proc);
//			change = 1; // idem;
//		ft_printf("proc live = %d\n", proc->live);
		if (!vm->visu.active)
			ft_printf("\n");
//		if (!proc_lst->next && change) // idem
//			display_arena((unsigned char *)vm->arena); // idem
		proc_lst = proc_lst->next;
	}
}

/*
** Core of game progression | calls itself until cycles to end = 0 or only 1
** player left
** Each turn: 
** Detect if end of cycle
** Loop through players:
**	- move forward amount of latest instruction (or 1 if no valid instruction)
**	- check if valid instruction
*/


int		play(t_vm *vm)
{
//	display(vm, 0, CYCLE_NBR);
	while (++vm->cycle && !handle_end_cycle(vm, &vm->cycle))
	{
		++vm->total_cycle;
//		ft_printf("\n%scycle = %d | %s ", COLF_BGREY, vm->cycle, MSG_CYCLES_REMAINING);
//		ft_printf(" [ %d ] %s\n", vm->c_to_die - vm->cycle, COLF_OFF);
		process_cycle(vm);
	}
	return (0);
}
