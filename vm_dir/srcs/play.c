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
	vm->live.nb = 0;
	if (vm->live.nb >= NBR_LIVE)
	{
		display(vm, NULL, RESIZE, LIVES_TURN);
		display(vm, NULL, RESIZE, NEW_RESIZE)
		vm->live.total_pl = 0;
		vm->checks = MAX_CHECKS ;
		vm->c_to_die -= CYCLE_DELTA;
		return;;
	}
	vm->live.total_pl = 0;
	display(vm, NULL, RESIZE, AUTO_RESIZE);
	if (!--vm->checks)
	{
		vm->checks = MAX_CHECKS;
		vm->c_to_die -= CYCLE_DELTA;
		display(vm, NULL, RESIZE, NEW_RESIZE)
	}
//	else if (++vm->checks)
//	
//	{
//		ft_printf("%s%scycle duration stays unchanged\n%s%s", COLF_BGREY, COLB_OFF, COLF_OFF, COLB_OFF);
//	}
	
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
			display(NULL, vm, PLAYER, PL_DEATH);
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
	if (proc->cycle > 0)
	{
		display(NULL, proc, PLAYER, PL_CYCLE);
		--proc->cycle;
		return ;
	}
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction(vm->arena, &ins, proc->pc, MEM_SIZE)))
	{
		f_ins[(int)ins.op.opcode](vm, ins.params, pl);
		i = -1;
		vm->proc[pl].cycle = g_op_tab[(int)ins.op.opcode - 1].nb_cycles;
		display(NULL, proc, PLAYER, PL_CYCLE);
		ft_printf("%s.... %d%s ", COL_WAIT, vm->proc[pl].cycle, COLF_OFF);
		ft_printf("%s%s%s", COL_VALIDINS, ins.op.description, COLF_OFF);
		if (ins.op.opcode == LIVE)
			ft_printf(" %s>>>%s %s%s%s", COL_VALIDINS, COLF_OFF, vm->color.player[vm->live.last_pl * 2 + 1], vm->player[vm->live.last_pl].name, COLB_OFF);
		return (ret);
	}
	else
	{
		display(NULL, NULL, TURN, MOVE_ONE);
//		++vm->proc[pl].pc;
//		ft_printf("%sMove forward... %s ", COLF_OFF, COLF_OFF);
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

	display(vm , NULL, TURN, CYCLE_NBR);
	if (cycle == vm->c_to_die)
	{
		reset_live_allprocesses(vm);
		if ((vm->live.total_pl <= 1 && vm->live.last_pl != -1) || vm->dead == vm->nb_players || !vm->c_to_die)
		{
			display(vm, NULL, PLAYER, PL_VICTORY);
			return (1);
		}
		if (vm->live.last_pl >= 0)
		{
			display(vm, NULL, TURN, CYCLE_END);
				check_resize_cycle(vm, &cycle);
		}
		vm->live.total_pl = 0;
		cycle = 0;
		display(vm, NULL, TURN, CYCLE_NBR);
	}
	pl = vm->nb_players - 1;
	players = vm->proc;
	ret_ins = 0;
	while (players)
	{
		proc = ((t_process *)players->content);
		proc->pc = (proc->pc + ret_ins) % MEM_SIZE;
		
		ft_printf(" %s%s%d %s%s ", vm->color.player[i * 2 + 1], PLAYER_LABEL, ((t_process *)players->content)->num, COLF_OFF, COLB_OFF);
		launch_instruction(vm, players, pl);
		ft_printf("%50s[%d]\n", "", ((t_process *)players->content)->pc);
		players = players->next;
	}
	++cycle;
	return (play(vm));
}
