/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 22:42:35 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

static void			check_resize_cycle(t_vm *vm, int *cycle)
{
	*cycle = 1;
	vm->live.nb = 0;
	if (vm->live.nb >= NBR_LIVE)
	{
		display(vm, 0, LIVES_TURN);
		display(vm, 0, NEW_RESIZE);
		vm->live.total_pl = 0;
		vm->checks = MAX_CHECKS ;
		vm->c_to_die -= CYCLE_DELTA;
		return;;
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

static void		reset_live_allprocesses(t_vm *vm)
{
	int i;
	t_list	*players;
	t_process *proc;
	t_list	*tmp;

	players = vm->proc;

	i = vm->nb_players;
	while (players)
	{
		 
		proc = ((t_process *)players->content);
		display(vm, proc->id, PL_DEATH);
		tmp->next = players->next;
		ft_lstdel_ptr(&players);
		players = tmp;
		++vm->dead;
		if (tmp != players)
			tmp = tmp->next;
		players = players->next;
	}
}

static int		launch_instruction(t_vm *vm, t_process *proc, int pl)
{
	t_instruction	ins;
	int				ret;
	int				i;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_parameter arg[3], int pl) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor,
		&ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork, &ins_aff};

	if (proc->cycle > 0)
	{
		ft_printf("%*s", PAD_INS, "");
		display(vm, 0, PL_CYCLE);
		--proc->cycle;
		return (1);
	}
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction(vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
		f_ins[(int)ins.op.opcode](vm, ins.params, pl);
		i = -1;
		proc->cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		ft_printf("%s >>> %*-s%s", COLF_GREEN, PAD_INS - 5, ins.op.description, COLF_OFF);
		display(vm, proc->id, PL_CYCLE);
		--proc->cycle; // voir si pertinent
//		ft_printf("%s.... %d%s ", COL_WAIT, proc->cycle, COLF_OFF);
		if (ins.op.opcode == LIVE)
			display(vm, vm->live.last_pl, LAST_LIVE);
//			ft_printf(" %s>>>%s %s%s%s", COL_VALIDINS, COLF_OFF, vm->color.player[vm->live.last_pl * 2 + 1], vm->player[vm->live.last_pl].name, COLB_OFF);
		proc->ins_cycle = ret;
		return (ret);
	}
	else
	{
		display(vm, proc->id, MOVE_ONE);
//		++vm->proc[pl].pc;
//		ft_printf("%sMove forward... %s ", COLF_OFF, COLF_OFF);
		return (0);
	}
}

int		play(t_vm *vm)
{
	int				pl;
	t_list				*players;
	t_process			*proc;

	display(vm, 0, CYCLE_NBR);
	if (vm->cycle == vm->c_to_die)
	{
		reset_live_allprocesses(vm);
		if ((vm->live.total_pl <= 1 && vm->live.last_pl != -1) || vm->dead == vm->nb_players || !vm->c_to_die)
		{
			display(vm, 0, PL_VICTORY);
			return (1);
		}
		if (vm->live.last_pl >= 0)
		{
			display(vm, 0, CYCLE_END);
				check_resize_cycle(vm, &vm->cycle);
		}
		vm->live.total_pl = 0;
		vm->cycle = 0;
		display(vm, 0, CYCLE_NBR);
	}
	pl = vm->nb_players - 1;
	players = vm->proc;
	while (players)
	{
		proc = ((t_process *)(players->content));
		
		if (!proc->cycle)
			proc->pc = (proc->pc + proc->ins_cycle) % MEM_SIZE;
//		ft_printf("proc pc = %d\n", proc->pc);
		ft_printf("%s %-*d", LABEL_PLAYER, PAD_PLNAME, proc->id);
//		ft_printf(" %s%s%d %s%s ", vm->color.player[i * 2 + 1], PLAYER_LABEL, ((t_process *)players->content)->num, COLF_OFF, COLB_OFF);
		launch_instruction(vm, proc, pl);
		display(vm, proc->id, PL_PC);
//		ft_printf("%50s[%d]\n", "", ((t_process *)players->content)->pc);
		players = players->next;
	}
	++vm->cycle;
	return (play(vm));
}
