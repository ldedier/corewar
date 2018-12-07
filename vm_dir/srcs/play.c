/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 22:44:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			check_resize_cycle(t_vm *vm, int *cycle)
{
	if (vm->nb_live >= NBR_LIVE)
	{
		vm->max_checks = 0;
		vm->nb_live = 0;
		vm->c_to_die -= CYCLE_DELTA;
	}
	else if (vm->max_checks >= MAX_CHECKS)
	{
		vm->max_checks = 0;
		vm->c_to_die -= CYCLE_DELTA;
	}
	else if (++vm->max_checks)
		return (0);
	*cycle = 0;
	return (1);
}


static void		reset_live_allprocesses(t_process *proc[MAX_PLAYERS + 1])
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		(*proc)[i].live = 0;
}

static int		stay_alive(t_vm *vm, t_process proc, int index)
{
	if (proc.live == 1)
	{
		ft_printf("Player %d [%s] is alive !\n", index, vm->player[index].name);
		return (1);
	}
	return (0);
}

int			launch_instruction(t_vm *vm, t_process *proc)
{
	t_instruction	ins;
	int				ret;
	int				i;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};

	if (--proc->cycle >= 0 && ft_printf(".... "))
		return (1);
	ft_printf("launch instruction | proc cycle = %d, proc->pc = %d\n", proc->cycle, proc->pc);//
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction((char *)vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
		ft_printf("ret  = %d\n", ret);
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
		i = -1;
		while (++i <= ret)
			proc->pc += ((proc->pc + 1) < MEM_SIZE) ? 1 : 0;
		proc->cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
//		ft_printf("tabcycle in %d = %d\n", ins.op.opcode, proc->cycle);
		return (0/*g_op_tab[(int)ins.op.opcode].nb_cycles*/);
	}
	proc->cycle++;
	proc->pc = (proc->pc == MEM_SIZE - 1 ? 0 : proc->pc + 1);
			ft_printf("new pc = %d\n", proc->pc);
	return (0);
}


int		play(t_vm *vm, t_process **proc)
{
	static int			cycle;
	int				pl;
	static int			total_live = MAX_PLAYERS;
	static int			last = -1;

//	ft_printf("play | cycle = %d total live = %d CTODIE = %d\n", cycle, total_live, vm->c_to_die);//
	if ((cycle && !total_live) || (total_live == 1 || !vm->c_to_die))
	{
		ft_printf("player %d [%s] wins!\n", last, vm->player[last].name);
		return (1);
	}
	total_live = 0;
	if (cycle == vm->c_to_die)
	{
		check_resize_cycle(vm, &cycle);
		reset_live_allprocesses(proc);
	}
	pl = vm->nb_players - 1;
//	ft_printf("players from 0 to %d\n", pl);
	while (pl >= 0)
	{
		if (!(*proc)[pl].cycle)
			ft_printf("\n\nPLAYER %d | pc = %d | live = %d: \n", vm->nb_players - pl, (*proc)[pl].pc, (*proc)[pl].live);//
		if (last != -1 && !(*proc)[pl].live && !stay_alive(vm, (*proc)[pl], pl) && cycle == vm->c_to_die)
			(*proc)[pl].live = DEAD;
		else if (++total_live)
			last = pl;
//		ft_printf("PC %d before in %d\n", pl, (*proc)[pl].pc);//
		if ((*proc)[pl].live != DEAD)
			launch_instruction(vm, &(*proc)[pl]);
//		ft_printf("PC %d after in %d\n", pl, (*proc)[pl].pc);//
		--pl;
	}
	++cycle;
	return (play(vm, proc));
}
