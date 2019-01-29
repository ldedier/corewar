/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:27:59 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/22 16:37:55 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_players function initializes each player's structures' parameters to
** their default value
*/

void			init_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = NULL;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 0;
		ft_bzero(vm->player[i].aff_buf, MAX_AFF_LEN);
	}
}

/*
** init_processes function initializes each player's starting process.
*/

int				init_processes(t_vm *vm)
{
	int		i;
	int		index;
	int		start;

	i = -1;
	index = 1;
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant && ++index && !add_process(vm, i, start))
			return (0);
		vm->player[i].nb_proc = 1;
		vm->winner = ((t_process *)(vm->proc->content))->player;
	}
	return (1);
}
