/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 16:29:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/20 17:03:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		process_play(t_vm *vm)
{
	static double	cycle_iterator = 0;
	int				nb_cycles;
	int				i;

	if (!(vm->visu.time_manager.pause))
	{
		cycle_iterator += vm->visu.time_manager.cycles_per_turn;
		nb_cycles = (int)cycle_iterator;
		i = nb_cycles;
		while (i-- && !(vm->cycle == vm->c_to_die &&
				!handle_end_cycle(vm, &vm->cycle)))
		{
			process_cycle(vm);
			++vm->cycle;
		}
		cycle_iterator -= nb_cycles;
	}
	return (0);
}

int		process(t_vm *vm)
{
	if (vm->visu.phase == PHASE_PLAY)
		return (process_play(vm));
	return (0);
}
