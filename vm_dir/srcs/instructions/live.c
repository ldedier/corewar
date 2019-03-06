/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:34 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 14:00:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** get_player_num function retrieves the player if the number given in
** the parameter has been attributed
*/

static t_player	*get_player_num(t_vm *vm, int num)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->player[i].num == num && vm->player[i].relevant)
			return (&vm->player[i]);
	return (NULL);
}

/*
** [live] instruction declares the player whose number is [arg 1] alive.
**
** Takes 1 argument: the player's number. Undetermined behaviour if [arg 1]
** isn't a known player number.
*/

int				ins_live(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	t_player	*player;
	t_fade		*live;

	live = NULL;
	getval_param_dest(vm, proc, &arg[0], 1);
	proc->live = 1;
	++vm->issued_live;
	proc->live_cycle = vm->total_cycle;
	player = get_player_num(vm, arg[0].value);
	display_proc_ins(vm, proc);
	if (player && ++vm->live)
	{
		player->live++;
		player->last_live_cycle = vm->total_cycle;
		vm->winner = player;
		if (!(live = (t_fade *)ft_memalloc(sizeof(t_fade))))
			return (FAILURE);
		live->pc = proc->pc;
		live->color = player->color.value;
		live->value = FADE_LEN;
		display_player_alive(vm, player);
		if (ft_add_to_list_ptr(&vm->live_ok, (void *)live, sizeof(t_fade)))
			return (FAILURE);
	}
	return (SUCCESS);
}
