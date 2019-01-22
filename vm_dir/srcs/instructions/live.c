/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:34 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/22 21:44:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [live] instruction declares the player whose number is [arg 1] alive.
**
** Takes 1 argument: the player's number. Undetermined behaviour if [arg 1]
** isn't a known player number.
*/

int		ins_live(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	t_player	*player;
	t_fade		*live;

	getval_param_dest(vm, proc, &arg[0], 1);
	proc->live = 1;
	proc->live_cycle = vm->total_cycle;
	player = get_player_num(vm->proc, arg[0].value);
	ft_printf("arg0 value = %d player num = %d\n", arg[0].value, player); 
	if (player)
	{
		++vm->live;
		player->live++;
		player->last_live_cycle = vm->total_cycle;
		vm->winner = player;
		if (!(vm->visu.active))
			display(vm, proc, MSG_ALIVE);
		live = (t_fade *)ft_memalloc(sizeof(t_fade));
		live->pc = proc->pc;
		live->color = *(int *)player->color.value;
		live->value = /*vm->cycle +*/ FADE_LEN;
		if (ft_add_to_list_ptr(&vm->live_ok, (void *)live, sizeof(t_fade)))
			return (FAILURE);
	}
	return (SUCCESS);
}
