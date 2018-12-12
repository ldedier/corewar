/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 21:56:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display(t_vm *vm, int pl, int type)
{
	static void (*display[NB_GAME_MSG])(t_vm *vm, int pl) = {
		&pl_pc, &pl_cycle, pl_live, &pl_death, &pl_victory,
		&lives_turn, &cycles_to_autoresize, &resize,
		&move_one, &last_live, &cycle_nb, &cycle_end};
	
//	ft_printf("type color = %d\n", type);
	color_on(vm->color, type);
//	ft_printf("display type = %d\n", type);
//	ft_printf("type color after set color on = %d\n", type);
	display[type](vm, pl);
	color_off();
}
