/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:15:00 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/07 19:44:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** clear arena and metarena, reset game indicators, free all processes
*/

void			clear_vm(t_vm *vm)
{
	int		i;

	i = -1;
	vm->live = 0;
	vm->nb = 1;
	vm->total_cycle = 0;
	vm->cycle = 0;
	vm->c_to_die = CYCLE_TO_DIE;
	ft_bzero(vm->arena, MEM_SIZE);
	while (vm->proc)
		ft_lstpop(&vm->proc);
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].live = 0;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 1;
	}
}
/*
** init_players function initializes each player's structures' parameters to
** their default value
*/

static void		init_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = 1;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 0;
		vm->player[i].num_type = -1;
		ft_bzero(vm->player[i].aff_buf, MAX_AFF_LEN);
	}
}

void			init_metarena(t_vm *vm)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_bzero((void *)&vm->metarena[i], sizeof(t_metadata));
		vm->metarena[i].process_color = -1;
		vm->metarena[i].content_color_index = 0;
	}
}

/*
** init_vm function initializes our corewar VM's environment by setting all
** its parametzers to their default value.
*/

void			init_vm(t_vm *vm, char **argv)
{
	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = -1;
	vm->checks = MAX_CHECKS;
	vm->live = 0;
	vm->client.active = 0;
	vm->client.port = 0;
	vm->visu.active = 0;
	vm->nb = -1;
	vm->total_cycle = 1;
	vm->cycle = 1;
	vm->nb_players = 0;
	vm->display.code = 0;
	vm->issued_live = 0;
	vm->proc = NULL;
	vm->display.status = OFF;
	ft_bzero(&vm->color, sizeof(t_color));
	init_players(vm);
}
