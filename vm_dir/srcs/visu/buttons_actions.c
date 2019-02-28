/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/27 16:17:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_delete_player(t_vm *vm, t_button *this, t_ixy xy)
{
	this->button_union.player->relevant = 0;
	dispatch_players(vm, NULL);
	this->visible = 0;
	ft_update_cursor(vm, xy);
	return (0);
}

int		start_fight(t_vm *vm)
{
	t_ixy xy;

	if (vm->nb_players)
	{
		vm->visu.phase = PHASE_PLAY;
		SDL_GetMouseState(&xy.x, &xy.y);
		ft_update_cursor(vm, xy);
		if (!init_processes(vm))
			return (1);
	}
	return (0);
}

int		go_back(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	clear_vm(vm);
	vm->visu.time_manager.cycles_per_turn = INIT_CYCLES_PER_TURN;
	dispatch_players_init(vm);
	vm->visu.phase = PHASE_INIT;
	ft_update_cursor(vm, xy);
	return (0);
}

int		fight(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)this;
	(void)xy;
	if (start_fight(vm))
		return (1);
	return (0);
}

int		clean_arena(t_vm *vm, t_button *this, t_ixy xy)
{
	int i;

	(void)this;
	(void)xy;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->visu.positions.arena_slots[i].close.visible = 0;
		i++;
	}
	dispatch_players(vm, NULL);
	return (0);
}
