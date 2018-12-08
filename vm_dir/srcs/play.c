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

void			check_resize_cycle(t_vm *vm, int *cycle)
{
	*cycle = 1;
	ft_printf("max checks = %d\n", vm->max_checks);
	if (vm->nb_live >= NBR_LIVE)
	{
		vm->max_checks = 0;
		vm->c_to_die -= CYCLE_DELTA;
		ft_printf("Too many lives! new cycle length to die: %d\n", vm->c_to_die);
		return;;
	}
	vm->nb_live = 0;
	if (vm->max_checks >= MAX_CHECKS)
	{
		vm->max_checks = 0;
		vm->c_to_die -= CYCLE_DELTA;
		ft_printf("%d since last resize! new cycle length to die: %d\n", vm->c_to_die, vm->c_to_die + CYCLE_DELTA);
	}
	else if (++vm->max_checks)
	{
		ft_printf("%s%scycle duration stays unchanged\n%s%s", COLF_BGREY, COLB_OFF, COLF_OFF, COLB_OFF);
	}
}


static void		reset_live_allprocesses(t_vm *vm, t_process *proc[MAX_PLAYERS + 1])
{
	int i;

	i = vm->nb_players;
	while (--i >= 0)
	{
		if ((*proc)[i].live == 0)
		{
			ft_printf("%s%s PLAYER %d died %s%s\n", COL_FDEAD, COL_BDEAD, vm->nb_players - i, COLF_OFF, COLB_OFF);
			(*proc)[i].live = DEAD;

		}
		else
			(*proc)[i].live = 0;
	}
	vm->nb_live = 0;
}
	
void			launch_instruction(t_vm *vm, t_process *proc)
{
	t_instruction	ins;
	int				ret;
	int				i;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};

	if (--proc->cycle >= 0 && ft_printf("%s.... %d%s ", COL_WAIT, proc->cycle, COLF_OFF))
		return ;;
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction((char *)vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
//		ft_printf("ret = %d %svalid instruction >> %s%s ", ret, vm->color.player[(ins.op.opcode - 1) * 2], ins.op.description, COLF_OFF);
		i = -1;
		while (++i < ret)
		{
			proc->pc = ((proc->pc) < MEM_SIZE - 1) ? proc->pc + 1 : 0;
		}
		proc->cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		ft_printf("%s.... %d%s ", COL_WAIT, proc->cycle, COLF_OFF);
		return ;
	}
	else
	{
		++proc->pc;
//	ft_printf("proc pc = %d proc cycle = %d\n", proc->pc, proc->cycle);
		ft_printf("%sMove forward... %s ", COLF_OFF, COLF_OFF);
	}
}


int		play(t_vm *vm, t_process **proc)
{
	static int			cycle = 1;
	int				pl;
	static int			total_live = 0;
	static int			last = -1;

	ft_printf("\n%s CYCLE %d [ %d left to check lives ] %s\n", COLF_BGREY, cycle, vm->c_to_die - cycle, COLF_OFF);
	if (cycle == vm->c_to_die)
	{
		reset_live_allprocesses(vm, proc);
		if ((!total_live && last != -1) || (total_live == 1 || !vm->c_to_die) )
		{
			ft_printf("%splayer %d [%s]%s%s wins!\n", vm->color.player[last], vm->nb_players - last, vm->player[last].name, COLB_OFF, COLF_OFF);
			return (1);
		}
		if (last >= 0)
		{
			ft_printf("\n%s%s>>> END OF CYCLE %s%s | ", COL_FCYCLE, COL_BCYCLE, COLF_OFF, COLB_OFF);
			check_resize_cycle(vm, &cycle);
		}
		total_live = 0;
		cycle = 0;
		ft_printf("\n%s CYCLE %d [ %d left to check lives ] %s\n", COLF_BGREY, cycle, vm->c_to_die - cycle, COLF_OFF);
	}
	pl = vm->nb_players - 1;
	while (pl >= 0)
	{
		if ((*proc)[pl].live != DEAD)
		{
	
			ft_printf(" %s PLAYER %d %s%s ", vm->color.player[(vm->nb_players - pl - 1) * 2 + 1], vm->nb_players - pl, COLF_OFF, COLB_OFF);
			launch_instruction(vm, &(*proc)[pl]);
			if (vm->nb_live > total_live)
			{
				total_live = vm->nb_live;
				last = pl;
			}
		}
		ft_printf("\n");
		--pl;
	}
	++cycle;
	return (play(vm, proc));
}
