/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 15:14:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_register(t_process *proc)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		ft_printf("R%d: %d | ", i + 1, proc->reg[i]);
	ft_printf("\n");
}


void	display(t_vm *vm, t_process *proc, int type)
{
	static void (*display[NB_GAME_MSG])(t_vm *vm, t_process *proc) = {
		&pl_pc, &pl_cycle, pl_live, &pl_death, &pl_victory,
		&lives_turn, &cycles_to_autoresize, &resize,
		&move_one, &last_live, &cycle_nb, &cycle_end, &turn_player};
	if (type < LIVES_TURN || type == TURN_PLAYER)
		color_on_term(proc->player->color.index);
	display[type](vm, proc);
	color_off();
}
