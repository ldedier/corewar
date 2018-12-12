/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:53:10 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/10 22:26:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			check_resize_cycle(t_vm *vm, int *cycle)
{
	*cycle = 1;
	ft_printf("max checks = %d\n", vm->max_checks);
	if (vm->live.nb >= NBR_LIVE)
	{
	vm->live.nb = 0;
	vm->live.total_pl = 0;
		vm->max_checks = 0;
		vm->c_to_die -= CYCLE_DELTA;
		ft_printf("Too many lives! new cycle length to die: %d\n", vm->c_to_die);
		return;;
	}
	vm->live.nb = 0;
	vm->live.total_pl = 0;
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
		if (proc->live == 0)
		{
			ft_printf("%s%s PLAYER %d died %s%s\n", COL_FDEAD, COL_BDEAD, proc->num, COLF_OFF, COLB_OFF);
			tmp->next = players->next;
			free_str_pointer(&players)
			players = tmp;
			++vm->dead;
//			proc->live = DEAD;
//		}
		else
			proc->live = 0;
		if (tmp != players)
			tmp = tmp->next;
		players = players->next;
	}
}

static int		launch_instruction(t_vm *vm, t_list *player, int pl)
{
	t_instruction	ins;
	int				ret;
	int				i;
	t_process			*proc;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_parameter arg[3], int pl) = {NULL,
		&ins_live, &ins_ld, &ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor,
		&ins_zjmp, &ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork, &ins_aff};

	proc = ((t_process *)player->content);

//	ft_printf("cycle = %d\n", vm->proc[pl].cycle);
	if (proc->cycle > 0 && ft_printf("%s.... %d%s ", COL_WAIT, proc->cycle, COLF_OFF))
	{
		--proc->cycle;
		return ;
	}
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction(vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
		f_ins[(int)ins.op.opcode](vm, ins.params, pl);
		i = -1;
//		proc->pc = (proc->pc + ret) % MEM_SIZE;
//		while (++i < ret)
//			proc->pc = ((vm->proc[pl].pc) < MEM_SIZE - 1) ? vm->proc[pl].pc + 1 : 0;
//		ft_printf("new pc = %d\n", vm->proc[pl].pc);
//		ft_printf("nb cycles = %d\n", g_op_tab[(int)ins.op.opcode - 1].nb_cycles);
		vm->proc[pl].cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		ft_printf("%s.... %d%s ", COL_WAIT, vm->proc[pl].cycle, COLF_OFF);
		ft_printf("%s%s%s", COL_VALIDINS, ins.op.description, COLF_OFF);
		if (ins.op.opcode == LIVE)
			ft_printf(" %s>>>%s %s%s%s", COL_VALIDINS, COLF_OFF, vm->color.player[vm->live.last_pl * 2 + 1], vm->player[vm->live.last_pl].name, COLB_OFF);
		return (ret);
	}
	else
	{
//		++vm->proc[pl].pc;
		ft_printf("%sMove forward... %s ", COLF_OFF, COLF_OFF);
		return (1);
	}
}

int		play(t_vm *vm)
{
	static int			cycle = 1;
	int				pl;
	t_list				*players;
	int				ret_ins;
	t_process			*proc;

	ft_printf("\n%s CYCLE %d [ %d left to check lives ] %s\n", COLF_BGREY, cycle, vm->c_to_die - cycle, COLF_OFF);
	if (cycle == vm->c_to_die)
	{
		reset_live_allprocesses(vm);
		if ((vm->live.total_pl <= 1 && vm->live.last_pl != -1) || vm->dead == vm->nb_players || !vm->c_to_die)
		{
			ft_printf("%splayer %d [%s]%s%s wins!\n", vm->color.player[(vm->nb_players - vm->live.last_pl * 2) + 1], vm->nb_players - vm->live.last_pl, vm->player[vm->live.last_pl].name, COLB_OFF, COLF_OFF);
			return (1);
		}
		if (vm->live.last_pl >= 0)
		{
			ft_printf("\n%s%s>>> END OF CYCLE %s%s | ", COL_FCYCLE, COL_BCYCLE, COLF_OFF, COLB_OFF);
			check_resize_cycle(vm, &cycle);
		}
		vm->live.total_pl = 0;
		cycle = 0;
		ft_printf("\n%s CYCLE %d [ %d left to check lives ] %s\n", COLF_BGREY, cycle, vm->c_to_die - cycle, COLF_OFF);
	}
	pl = vm->nb_players - 1;
	players = vm->proc;
	ret_ins = 0;
	while (players)
	{
		proc = ((t_process *)players->content);
		if (proc->live != DEAD)
		{
			proc->pc = (proc->pc + ret_ins) % MEM_SIZE;
			ft_printf(" %s PLAYER %d %s%s ", vm->color.player[i * 2 + 1], ((t_process *)players->content)->num, COLF_OFF, COLB_OFF);
			launch_instruction(vm, players, pl);
			ft_printf("%50s[%d]\n", "", ((t_process *)players->content)->pc);
		}
		players = players->next;
	}
	++cycle;
	return (play(vm));
}
