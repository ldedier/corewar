/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/19 16:49:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_live_player(t_vm *vm, int op_code)
{
	t_player *player;

//	ft_printf("display live\n");
	if (op_code == LIVE)
	{
		player = get_player_num(vm->proc, vm->winner->num);
		display(vm, NULL, LAST_LIVE);
	}
}

void		display_ins_description(t_vm *vm, char *str, int opcode)
{
//	ft_printf("COUCOU description\n");
	ft_printf("%s >>> %*-s%s", COLF_CYAN, PAD_INS - 5, str, COLF_OFF);
	display_live_player(vm, opcode);
//	ft_printf("COUCOU description end\n");
}

void	display_registers(t_vm *vm)
{
	int i;
	t_list *proc;

	proc = vm->proc;
	ft_printf("*** DISPLAY REGISTERS ***\n\n");
//	ft_printf("proc = %d\n", proc);
	while (proc && proc->content)
	{
		i = -1;
//		ft_printf("Process in %d\n", ((t_process *)proc->content)->pc);
		while (++i < REG_NUMBER && proc->content)
			ft_printf("R%d: %d | ", i + 1, ((t_process *)proc->content)->reg[i]);
		ft_printf("\n\n");
		proc = proc->next;
	}
}

void		display(t_vm *vm, t_process *proc, int type)
{
	static void (*display[NB_GAME_MSG])(t_vm *vm, t_process *proc) = {
		&pl_pc, &pl_cycle, pl_live, &pl_death, &pl_victory,
		&lives_turn, &cycles_to_autoresize, &resize,
		&move_one, &last_live, &cycle_nb, &cycle_end, &turn_player};

	if (vm->visu.active)
		return ;
	if (vm->proc && (type < LIVES_TURN || type == TURN_PLAYER))
		color_on_term(proc->player->color.index);
	display[type](vm, proc);
	color_off();
}
