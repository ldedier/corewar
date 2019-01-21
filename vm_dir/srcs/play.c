/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/21 22:19:22 by emuckens         ###   ########.fr       */
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

static void			check_resize_cycle(t_vm *vm, int *cycle)
{
	(void)cycle;
	if (vm->live >= NBR_LIVE)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA < vm->c_to_die ? CYCLE_DELTA : vm->c_to_die;
		return ;
	}
	if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA < vm->c_to_die ? CYCLE_DELTA : vm->c_to_die;
		display(vm, NULL, NEW_RESIZE);
	}
}

static int		kill_process(t_vm *vm, t_list *proc)
{
	t_list	*tmp2;
	t_fade	*killed_proc;

	tmp2 = vm->proc;
	display(vm, (t_process *)proc->content, PL_DEATH);
	killed_proc = (t_fade *)ft_memalloc(sizeof(t_fade));
	killed_proc->pc = ((t_process *)proc->content)->pc;
	killed_proc->color =
					*((int *)((t_process *)proc->content)->player->color.value);
	killed_proc->value = MAX_FADE;
	--((t_process *)proc->content)->player->nb_proc;
	if (ft_add_to_list_ptr(&vm->killed_proc,
										(void *)killed_proc, sizeof(t_fade)))
		return (-1);
//	ft_printf("vm proc = %d vm proc next = %d proc = %d proc next = %d\n", vm->proc, vm->proc->next, proc, proc->next);
	while (tmp2 && tmp2->next && tmp2 != proc && tmp2->next != proc)
			tmp2 = tmp2->next;
//	ft_printf("tmp 2 = %d\n", tmp2);
	tmp2->next = proc->next;
//	ft_printf("vm proc = %d vm proc next = %d proc = %d proc next = %d\n", vm->proc, vm->proc->next, proc, proc->next);
	if (proc == vm->proc && !proc->next)
		vm->proc = NULL;
	else
		vm->proc = (proc == vm->proc) ? proc->next : vm->proc;
//	if (vm->proc)
//		ft_printf("AFTER vm proc = %d vm proc next = %d proc = %d proc next = %d\n", vm->proc, vm->proc->next, proc, proc->next);
	display_last_live(vm, (t_process *)proc->content);
	ft_memdel((void **)&proc->content);
	ft_memdel((void **)&proc);
//	ft_printf("KILL PROCESS | current winner is %s\n", vm->winner->cor_name);
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

	display(vm, NULL, CYCLE_END);
	proc_lst = vm->proc;
	while (proc_lst && (proc = ((t_process *)proc_lst->content)))
	{
//		ft_printf("proc live = %d\n", proc->live);
		if (!proc->live)
		{
//			ft_printf("kill process");
			if (kill_process(vm, proc_lst) == -1)
				return (-1);
		}
		else
		{
			proc->live = 0;
			proc->player->live = 0;
		}
		proc_lst = proc_lst->next;
	}
	vm->live = 0;
	return (0);
}

/*
** checks if latest instruction is still ongoing (via proc->cycle) and displays
*/

static int		last_instruction_unresolved(t_vm *vm, t_process *proc)
{
	t_pending *pending;

	(void)vm;
	pending = ((t_pending *)&proc->pending);
//	ft_printf("pending cycles = %d\n", pending->cycles);
	--pending->cycles;
	if (pending->cycles > 1)
	{
//		if (!vm->visu.active)
//		{
//			ft_printf("%*s", PAD_INS, "");
//			display(vm, proc, PL_CYCLE);
//			display(vm, proc, PL_PC);
//:w
//}
		return (1);
	}
	return (0);
}

void		execute_pending_action(t_vm *vm, t_process *proc)
{
	int			index;
	int			val;
	int			i;

	if (proc->pending.cycles == 1)
	{
		display_ins(vm, proc);
		display_move(vm, proc);
		proc->pc = (proc->pc + proc->pending.pc) % MEM_SIZE;

		if (proc->pending.dest == vm->arena && (i = -1))
		{
			while (++i < 4)
			{
				index = (proc->pending.dest_index + i) % MEM_SIZE;
				val = proc->pending.value & (0xFF << ((3 - i) * 8));
				*(char *)(proc->pending.dest + index) = val >> ((3 - i) * 8);
				vm->metarena[index].color_index = 5;
			//	vm->metarena[index].alt_color = 1;
			}
		}
		else if (proc->pending.dest)
		{
			proc->reg[proc->pending.dest_index] = proc->pending.value;
		}
		proc->pending.dest = NULL;
		ft_bzero((void *)&proc->pending.ins, sizeof(proc->pending.ins));

	}
}

/*
** Checks if last instruction is still running.
** Else, if there's a valid instruction at the current position, launches it,
** adjusts cycles, and displays. If not, moves on.
*/

static int		launch_instruction(t_vm *vm, t_process *proc)
{
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};
	if (last_instruction_unresolved(vm, proc))
		return (0);
	if (proc->pending.ins.op.opcode)
	{
		f_ins[(int)proc->pending.ins.op.opcode](vm, proc, proc->pending.ins.params);
		execute_pending_action(vm, proc);
		return (0);
	}
	proc->ins_bytelen = get_instruction(vm->arena, &proc->pending.ins, proc->pc, MEM_SIZE);
	
	if ((proc->ins_bytelen))
	{
		proc->pending.pc = proc->ins_bytelen;
		proc->pending.cycles = g_op_tab[(int)proc->pending.ins.op.opcode - 1].nb_cycles;
		return (1);
	}
		proc->pc += 1;
	return (0);
}

/*
** process_cycle
*/

void		process_cycle(t_vm *vm)
{
	t_list				*proc_lst;

	display_cycle(vm);
	if (vm->cycle >= vm->c_to_die)
	{
		reset_live_allprocesses(vm);
		check_resize_cycle(vm, &vm->cycle);
		vm->cycle = 0;
	}
	proc_lst = vm->proc;
//	ft_printf("check vm proc = %d prc next = %d\n", vm->proc, vm->proc->next);
	while (proc_lst)
	{
//		ft_printf("PROCESS CYCLE cycle = %d cycle to die = %d\n", vm->cycle, vm->c_to_die);
		display(vm, (t_process *)proc_lst->content, TURN_PLAYER);
		launch_instruction(vm, (t_process *)proc_lst->content);
//		if (!vm->visu.active)
//			ft_printf("\n");
		proc_lst = proc_lst->next;
	}
	++vm->cycle;
//	ft_printf("vm cycle = %d\n", vm->cycle);
	++vm->total_cycle;
}

int		fight_cores(t_vm *vm, t_player *pl1, t_player *pl2)
{
	vm->visu.active = 1;
	clear_vm(vm);
	ft_memmove(&vm->player[0], pl1, sizeof(t_player));
	ft_memmove(&vm->player[1], pl2, sizeof(t_player));
	vm->player[0].num = 1;
	vm->player[1].num = 2;
	vm->player[0].relevant = 1;
	vm->player[1].relevant = 1;
	vm->player[2].relevant = 0;
	vm->player[3].relevant = 0;
	dispatch_players_init(vm);
	if (!init_processes(vm))
		error_exit_msg(INIT_PROC_ERROR);
	while (vm->proc)
		process_cycle(vm);
	if (vm->winner == &vm->player[0])
		vm->winner = pl1;
	else
		vm->winner = pl2;
	return (0);
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
	display(vm, 0, CYCLE_NBR);
	while (vm->proc)
	{
//		ft_printf("\n%sPLAY cycle = %d | %s ", COLF_BGREY, vm->cycle,
//			MSG_CYCLES_REMAINING);
//
///	ft_printf(" [ %d ] %s\n", vm->c_to_die - vm->cycle, COLF_OFF);
		process_cycle(vm);
	}
	return (0);
}
