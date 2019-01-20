/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:34 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/20 16:47:48 by emuckens         ###   ########.fr       */
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

//	ft_printf("LIVE! total cycle = %d arg[0] = %d\n", vm->total_cycle, arg[0]);
	getval_param_dest(vm, proc, &arg[0], 1);
	proc->live = 1;
	player = get_player_num(vm->proc, arg[0].value);
//	ft_printf("player = %d player last live cycle = %d\n", player, vm->total_cycle);
	if (player)
	{
		++vm->live;
		player->live++;
		player->last_live_cycle = vm->total_cycle;
//		ft_printf("last live cycle = %d\n", player->last_live_cycle);
		vm->winner = player;
		if (!(vm->visu.active))
			ft_printf("A process declares the player %d(%s) alive.\n",
					player->num, player->name);
		live = (t_fade *)ft_memalloc(sizeof(t_fade));
		live->pc = proc->pc;
		live->color = *(int *)player->color.value;
		live->value = /*vm->cycle +*/ FADE_LEN;
		if (ft_add_to_list_ptr(&vm->live_ok, (void *)live, sizeof(t_fade)))
			return (FAILURE);
	}
	return (SUCCESS);
}
