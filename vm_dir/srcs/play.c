/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/19 16:41:17 by emuckens         ###   ########.fr       */
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
//	display(vm, NULL, LIVES_TURN);
//	display(vm, NULL, NEW_RESIZE);
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA < vm->c_to_die ? CYCLE_DELTA : vm->c_to_die;
		return;
	}
//display(vm, NULL, AUTO_RESIZE);
	if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA < vm->c_to_die ? CYCLE_DELTA : vm->c_to_die;
//	ft_printf("new cycle to die = %d\n", vm->c_to_die);
		display(vm, NULL, NEW_RESIZE);
	}
}

static int		kill_process(t_vm *vm, t_list *proc)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_fade	*killed_proc;

	tmp = proc;
	tmp2 = vm->proc;
	display(vm, (t_process *)proc->content, PL_DEATH);
	killed_proc = (t_fade *)ft_memalloc(sizeof(t_fade));
	killed_proc->pc = ((t_process *)proc->content)->pc;
	killed_proc->color = *((int *)((t_process *)proc->content)->player->color.value);
	killed_proc->value = MAX_FADE;
	--((t_process *)proc->content)->player->nb_proc;
	if (ft_add_to_list_ptr(&vm->killed_proc, (void *)killed_proc, sizeof(t_fade)))
		return (-1);
	while (tmp2 && /*proc &&*/ tmp2->next && tmp2->next != proc)
			tmp2 = tmp2->next;
	tmp2 = proc->next; // ? proc->next : NULL;
	if (proc == vm->proc && !proc->next)
		vm->proc = NULL;
	else
		vm->proc = (proc == vm->proc) ? tmp->next : vm->proc;
	ft_memdel((void **)&tmp->content);
	ft_memdel((void **)&tmp);
	return (0);
}

/*
** Upon reaching cycle end
** Scans all players, checks if they have lived previous turn;
** if so set live back to one, if not remove from process list;
*/

static int		reset_live_allprocesses(t_vm *vm)
{
	t_list		*proc_lst;
	t_process *proc;

	display(vm, NULL, CYCLE_END);
	proc_lst = vm->proc;
	while (proc_lst && (proc = ((t_process *)proc_lst->content)))
	{
		ft_printf("proc live = %d\n", proc->live);
		if (!proc->live)
		{
			ft_printf("kill process");
			if (kill_process(vm, proc_lst) == -1)
				return (-1);

//			return (0);
		}
		else
		{
			proc->live = 0;
			proc->player->live = 0;
		}
		vm->winner = proc->player;
		proc_lst = proc_lst->next;
	}
	return (0);
}

/*
** Checks if latest instruction is still ongoing (via proc->cycle) and display
*/

static int		last_instruction_unresolved(t_vm *vm, t_process *proc)
{
	t_pending *pending;

	pending = ((t_pending *)&proc->pending);
//	if (pending)
		--pending->cycles;
	if (pending->cycles > 0 && ft_printf("%*s", PAD_INS, ""))
	{
		ft_printf("pending cycles = %d\n", pending->cycles);
		display(vm, proc, PL_CYCLE);
		display(vm, proc, PL_PC);
		return (1);
	}
	return (0);
}

void		execute_pending_action(t_vm *vm, t_process *proc)
{
//	t_process	*proc;
	int			index;
	int			val;
	int			i;

//	proc = (t_process *)proc_lst->content;
	if (proc->pending.cycles == 0)
	{
		proc->pc = (proc->pc + proc->pending.pc - 1) % MEM_SIZE;
//		ft_printf("dest = %d\n", proc->pending.dest);
//		ft_printf("value before splitting by bytes = %d dest index = %d\n",
//			proc->pending.value, proc->pending.dest_index);
		if (proc->pending.dest == vm->arena && (i = -1))
		{
			while (++i < 4)
			{
				index = (proc->pending.dest_index + i) % MEM_SIZE;
				val = proc->pending.value & (0xFF << ((3 - i) * 8));
				*(char *)(proc->pending.dest + index) = val >> ((3 - i) * 8);
				vm->metarena[index].alt_color = 1;
			}
		}
		else if (proc->pending.dest)
			proc->reg[proc->pending.dest_index] = proc->pending.value;
		//IMPORTANT verif comportement si reg a modifier a index % MEMSIZE < 16
		proc->pending.dest = NULL;
		ft_printf("player pc = %d\n", proc->pc);//
		ft_printf("\n");//
		ft_bzero((void *)&proc->pending.ins, sizeof(proc->pending.ins));

	}
}




/*
** checks if last instruction is still running
** else, if there's a  valid instruction at current position launch it,
** adjust cycles, and display
** else move on
*/

static int		launch_instruction(t_vm *vm, t_process *proc)
{
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};
	ft_printf("LAUNCH INSTRUCTION\n");

	if (last_instruction_unresolved(vm, proc))
		return (0);
	if (proc->pending.ins.op.opcode)
	{
		f_ins[(int)proc->pending.ins.op.opcode](vm, proc, proc->pending.ins.params);
		display_ins_description(vm, proc->pending.ins.op.description, proc->pending.ins.op.opcode);
		execute_pending_action(vm, proc);
		return (0);
	}
	proc->ins_bytelen = get_instruction(vm->arena, &proc->pending.ins, proc->pc, MEM_SIZE);
	if ((proc->ins_bytelen))
	{
		proc->pending.pc = proc->ins_bytelen;
		proc->pending.cycles = g_op_tab[(int)proc->pending.ins.op.opcode - 1].nb_cycles;
//		display(vm, proc, PL_PC);
//		display(vm, proc, PL_CYCLE);
		return (1);
	}
		proc->pc += 1;
//	display(vm, proc, MOVE_ONE);
//	display(vm, proc, PL_PC);
	return (0);
}

/*
** If there's only 1 player or cycle_to_die = 0, displays winner and exits game,
** else checks if cycle_to_die should change value
*/
/*
int			handle_end_cycle(t_vm *vm, int *cycle)
{
//t_player *player;

	if (*cycle < vm->c_to_die)
		return (0);
	reset_live_allprocesses(vm);
//player = get_player_num(vm->proc, vm->live.winner->num);
	if (!vm->proc)
	{
		display(vm, NULL, PL_VICTORY);
		return (1);
	}
	*cycle = 0;
	check_resize_cycle(vm, cycle);
	return (0);
}
*/
/*
**process_cycle
*/

void		process_cycle(t_vm *vm)
{
	t_list				*proc_lst;

	if (vm->cycle >= CYCLE_TO_DIE)
	{
		reset_live_allprocesses(vm);
		check_resize_cycle(vm, &vm->cycle);
		vm->cycle = 1;
	}
	proc_lst = vm->proc;
	while (proc_lst)
	{
		display(vm, (t_process *)proc_lst->content, TURN_PLAYER);
		launch_instruction(vm, (t_process *)proc_lst->content);
		if (!vm->visu.active)
			ft_printf("\n");
		proc_lst = proc_lst->next;
	}
	++vm->cycle;
	ft_printf("vm cycle = %d\n", vm->cycle);
	++vm->total_cycle;
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
		ft_printf("CYCLE = %d TOTAL CYCLE = %d\n", vm->cycle, vm->total_cycle);
		ft_printf("\n%scycle = %d | %s ", COLF_BGREY, vm->cycle,
			MSG_CYCLES_REMAINING);
		ft_printf(" [ %d ] %s\n", vm->c_to_die - vm->cycle, COLF_OFF);
		process_cycle(vm);
	}
	return (0);
}
