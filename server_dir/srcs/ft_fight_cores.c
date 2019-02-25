/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fight_cores.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:53:24 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/25 16:55:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** Generates and runs through game for 2 players, to communicate result to
** server for one-on-one match and subsequent score computation
*/

int		fight_cores(t_vm *vm, t_player *pl1, t_player *pl2)
{
	clear_vm(vm);
	ft_memmove(&vm->player[0], pl1, sizeof(t_player));
	ft_memmove(&vm->player[1], pl2, sizeof(t_player));
	vm->player[0].num = 1; //faire par pointeurs...
	vm->player[1].num = 2;
	vm->player[0].relevant = 1;
	vm->player[1].relevant = 1;
	vm->player[2].relevant = 0;
	vm->player[3].relevant = 0;
	dispatch_players_init(vm);
	if (!init_processes(vm))
		return (error_exit_msg(vm, INIT_PROC_ERROR));
	while (vm->proc)
	{
		process_cycle(vm);
	}
	if (vm->winner == &vm->player[0])
		vm->winner = pl1;
	else
		vm->winner = pl2;
	vm->visu.active = 0;
	return (SUCCESS);
}
