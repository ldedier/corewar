/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 16:29:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 19:44:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	process_play(t_vm *vm, double nb_cycles_db)
{
	static double	cycle_iterator = 0;
	int				nb_cycles;
	int				i;

	cycle_iterator += nb_cycles_db;
	nb_cycles = (int)cycle_iterator;
	i = nb_cycles;
	while (i-- && vm->proc)
	{
		if (play_one_cycle(vm))
			return (1);
	}
	cycle_iterator -= nb_cycles;
	return (0);
}

int			process(t_vm *vm)
{
	if (vm->visu.phase == PHASE_PLAY)
	{
		if (!(vm->visu.time_manager.pause))
			return (process_play(vm, vm->visu.time_manager.cycles_per_turn));
	}
	return (0);
}
