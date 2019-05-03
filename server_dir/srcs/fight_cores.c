/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight_cores.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:35 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/11 14:25:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			dispatch_players_nodisplay(t_vm *vm)
{
	int			index;
	int			i;
	int			j;
	int			start;

	i = -1;
	index = 0;
	update_nb_players(vm);
	while (++i < MAX_PLAYERS)
	{
		set_color_sdl(vm, &vm->player[i]);
		if (vm->player[i].relevant && ++index)
		{
			j = -1;
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
		vm->local_player[i] = vm->player[i];
		vm->local_player[i].color.value = 1;
		vm->local_player[i].num = vm->nb;
	}
}

/*
** Generates and runs through game for 2 players, to communicate result to
** server for one-on-one match and subsequent score computation
*/

int					fight_cores(t_vm *vm, t_player *pl1, t_player *pl2)
{
	clear_vm(vm);
	ft_memmove(&vm->player[0], pl1, sizeof(t_player));
	ft_memmove(&vm->player[1], pl2, sizeof(t_player));
	vm->player[0].num = 1;
	vm->player[1].num = 2;
	vm->player[0].relevant = 1;
	vm->player[1].relevant = 1;
	vm->player[2].relevant = 0;
	vm->player[3].relevant = 0;
	dispatch_players_nodisplay(vm);
	if (init_processes(vm))
		return (error_exit_msg(vm, INIT_PROC_ERROR));
	while (vm->proc)
		play_one_cycle(vm);
	if (vm->winner == &vm->player[0])
		vm->winner = pl1;
	else
		vm->winner = pl2;
	vm->visu.active = 0;
	return (SUCCESS);
}
