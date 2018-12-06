/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 16:59:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_processes(t_vm *vm, t_process **proc)
{
	int i;
	int op = 1;
	static char reg[REG_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	t_parameter arg[3];

	i = -1;
	(void)arg;
	while (++i < MAX_PLAYERS)
	{
		(*proc)[i].id = i;
		(*proc)[i].pc = i * (MEM_SIZE / MAX_PLAYERS); // verifier calcul
		(*proc)[i].cycle = 1;
		(*proc)[i].live = 1;

		ft_memmove((void *)(*proc)[i].reg, (void *)reg, REG_NUMBER);
		arg[0].value = i;
		arg[0].nb_bytes = 4;
		ft_memmove((void *)(vm->arena + i * 1024), (void *)&op, sizeof(char));
		ft_memmove((void *)(vm->arena + i * 1024 + 4), (void *)&arg[0].value, sizeof(int));

		//		display_arena(vm->arena);
		//		ins_live(vm, *proc, arg);
		//		ft_printf("i = %d | arg[0] = %d arg[1] = %d\n", i, i * 2, reg[i]);
		//		arg[0].value = i * 2;
		//		arg[0].nb_bytes = 4;
		//		arg[1].value = reg[i];
		//		arg[1].nb_bytes = 1;
		//		arg[3].val = 0;
		//		arg[3].nb_bytes = 0;
		//		ins_st(vm, *proc, arg);
	}
}

void		declare_winner(t_vm *vm, t_process **proc)
{
	int 	i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if ((*proc)[i].live == 1)
			ft_printf("player %d [%s] wins!\n", i, vm->player[i].name);
	// Incorrect, penser a detecter le DERNIER live
	// plus gerer cas d'egalite, si c_to_die = 0 ou plusieurs live sur le meme cycle?
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

int			launch_instruction(t_vm *vm, t_process *proc, t_op *tab)
{
	t_instruction	ins;
	int				ret;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};

	ft_printf("launch instruction | proc cycle = %d\n", proc->cycle);
	if (--proc->cycle)
		return (1);
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction((char *)vm->arena, (t_op *)tab, proc->pc, &ins)))
	{
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
		proc->pc = (proc->pc + ret) & MEM_SIZE;
		return (tab[(int)ins.op.opcode].nb_cycles);
	}
	proc->pc = (proc->pc == MEM_SIZE - 1 ? 0 : proc->pc + 1);
	return (1);
}


int		play(t_vm *vm, t_process **proc, t_op *tab)
{
	static int			cycle;
	int					pl;
	static int					total_live;

	ft_printf("play | cycle = %d total live = %d\n", cycle, total_live);
	if (cycle && !total_live)
	{	
		ft_printf("no winner!\n");
		return (0);

	}	
	if (total_live == 1 || !vm->c_to_die)
	{
		declare_winner(vm, proc);
		return (1);
	}
	total_live = 0;
	if (cycle == vm->c_to_die)
	{
		check_resize_cycle(vm, &cycle);
		reset_live_allprocesses(proc);
	}
	//	pl = MAX_PLAYERS;
	pl = 2;
	while (pl--)
	{
		ft_printf("PLAYER %d | pc = %d: \n", pl, (*proc)[pl].pc);
		if (!stay_alive(vm, (*proc)[pl], pl))
			(*proc)[pl].live = DEAD;
		else
			++total_live;
		if ((*proc)[pl].live != DEAD)
			(*proc)[pl].cycle += launch_instruction(vm, *proc, tab);
		ft_printf("PC %d in %d\n", pl, (*proc)[pl].pc);
	}
	++cycle;
	return (play(vm, proc, tab));
}
