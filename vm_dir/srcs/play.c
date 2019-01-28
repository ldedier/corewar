/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/28 21:38:56 by emuckens         ###   ########.fr       */
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
//	*cycle = 0;
	if (vm->issued_live >= NBR_LIVE)
	{
		vm->checks = MAX_CHECKS;
//		vm->c_to_die -= CYCLE_DELTA;
	}
	else if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
//		vm->c_to_die -= CYCLE_DELTA;
	}
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
//	if (!tmp->next)
//		ft_printf("coucou\n");
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
//		if (((t_process *)tmp->content)->nb == 0)
//			ft_printf("CYCLE %d\n", vm->total_cycle);
//		ft_printf("proc #%d\n", ((t_process *)tmp->content)->nb);
		tmp = tmp->next;
		++i;
	}
	return (i);
}


static int		kill_process(t_vm *vm, t_list **proc_lst, t_list *proc)
{
	t_fade	*killed_proc;
	(void)*proc_lst;

	killed_proc = (t_fade *)ft_memalloc(sizeof(t_fade));
	killed_proc->pc = ((t_process *)proc->content)->pc;
	killed_proc->color =
					*((int *)((t_process *)proc->content)->player->color.value);
	killed_proc->value = MAX_FADE;
	--((t_process *)proc->content)->player->nb_proc;
	if (ft_add_to_list_ptr(&vm->killed_proc,
										(void *)killed_proc, sizeof(t_fade)))
		return (-1);
//	if (((t_process *)proc->content)->nb == 19)
//		ft_printf("proc = %d\n", proc);
//	if (proc && proc == *proc_lst /*&& ft_printf("special case\n")*/)
//	{
//		ft_printf("coucou lala\n");
//		ft_printf("proc lst = %d next = %d\n", *proc_lst, (*proc_lst)->next);
//		*proc_lst = (*proc_lst)->next;
//		ft_printf("after proc lst = %d\n", *proc_lst);
//	}
//	else
//	if (vm->proc)
//	{
		kill_adjust_ptr(&vm->proc, &proc); 
		display_last_live(vm, (t_process *)proc->content);
//	}
	ft_memdel((void **)&proc->content);
	ft_memdel((void **)&proc);
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

	proc_lst = vm->proc;
	while (proc_lst && (proc = ((t_process *)proc_lst->content)))
	{
//		if (vm->c_to_die == 1386)
//			ft_printf("proc number = %d total cycle = %d proc live cycle = %d | delta = %d\n", proc->nb, vm->total_cycle, proc->live_cycle, vm->total_cycle - proc->live_cycle);
		if (vm->total_cycle - proc->live_cycle >= vm->c_to_die)
		{

//			if (proc->nb == 19)
//				ft_printf("kill proc 19\n");
//			ft_printf("before kill\n");
//			list_size(vm->proc);
			kill_process(vm, &vm->proc, proc_lst);	
//			ft_printf("vm proc = %d\n", vm->proc);
//			ft_printf("after kill\n");
//			ft_printf("\n\n");
//			list_size(vm->proc);
//			ft_printf("\n\n");

		}
		else
		{
//			if (proc->nb == 19)
//				ft_printf("reset proc 19\n");
			proc->live = 0;
			proc->player->live = 0;
		}
//		ft_printf("listsize = %d\n", list_size(vm, vm->proc));
	
		proc_lst = proc_lst->next;
	//	if (proc_st == vm->proc)
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
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or,
		&ins_xor, &ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi,
		&ins_lfork, &ins_aff};
//	ft_printf("nb cycles = %d\n", proc->pending_ins.op.nb_cycles - 1);
	if (--proc->pending_ins.op.nb_cycles > 1)
		return (0);
//		ft_printf("\nop code = %d, cycles = %d", proc->pending_ins.op.opcode, proc->pending_ins.op.nb_cycles);
	if (proc->pending_ins.op.nb_cycles == 1)
	{
		if (proc->pending_ins.op.opcode > 0)
			f_ins[ft_abs((int)proc->pending_ins.op.opcode)](vm, proc, proc->pending_ins.params);// && !vm->visu.active && (vm->display & (1 << MSG_INS));
//			ft_printf("coucou\n");&& !vm->visu.active && (vm->display & (1 << MSG_INS))&& !vm->visu.active && (vm->display & (1 << MSG_INS));;
///		display_ins(vm, proc)
		display_move(vm, proc);
		if (proc->pending_ins.op.opcode != ZJMP || !proc->carry)
	//	if (proc->ins_bytelen)
			proc->pc += proc->ins_bytelen;
		ft_bzero(&proc->pending_ins, sizeof(t_instruction));
		proc->ins_bytelen = 0;
		return (0);
	}
	proc->ins_bytelen = get_instruction(vm->arena, &proc->pending_ins, proc->pc, MEM_SIZE);
//	ft_printf("bytelen = %d, has ocp  = %d\n", proc->ins_bytelen, proc->pending_ins.op.has_ocp);
	if (!(proc->ins_bytelen))
	{

//		proc->ins_bytelen = -1 - proc->pending_ins.op.has_ocp;
		proc->ins_bytelen = proc->pending_ins.op.opcode;
//		ft_printf("failed instruction, proc ins bytlen = %d, cycles = %d\n", proc->ins_bytelen, proc->pending_ins.op.nb_cycles);
//		proc->pc += proc->pending_ins.op.opcode;
		ft_bzero(&proc->pending_ins, sizeof(t_instruction));
	}
	else if (proc->ins_bytelen < 0)
	{
		++proc->pc;
//		proc->pc += ft_abs(proc->ins_bytelen); // anciennement proc->pc + 1
		proc->pending_ins.op.opcode *= -1;
	}
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

void		process_cycle(t_vm *vm)
{
	t_list				*proc_lst;
	t_process			*proc;
	int					new_ctodie;

	display_cycle(vm);
		proc_lst = vm->proc;
//			ft_printf("resize, new cycle = %d\n", vm->cycle);
//			return ;
// 	list_size(vm, vm->proc);
	while (proc_lst)
	{
		proc = (t_process *)proc_lst->content;
//		if (vm->cycle <= 1386 && proc->nb == 19)
//			ft_printf("proc 19 pc = %d, total cycle = %d last live = %d, ctodie = %d, delta = %d, proc live = %d\n", proc->pc, vm->total_cycle, proc->live_cycle, vm->c_to_die, vm->total_cycle - proc->live_cycle, proc->live);
		launch_instruction(vm, proc);
		proc_lst = proc_lst->next;
	}
//	if (vm->cycle >= vm->c_to_die)
	if (vm->cycle >= vm->c_to_die)
	{
//		check_resize_cycle(vm, &vm->cycle);
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
//	vm->visu.active = 1;
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






