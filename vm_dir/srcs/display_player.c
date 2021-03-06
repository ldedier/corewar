/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:04:17 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/11 19:47:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_player_intro(t_vm *vm, t_player *player)
{
	if (vm->visu.active)
		return ;
	ft_printf("%s\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !%s",
			player->color.term,
			player->num * player->num_type,
			player->algo_len,
			player->name,
			player->comm[0] ? player->comm : "",
			vm->color.off);
}

void		display_player_alive(t_vm *vm, t_player *player)
{
	if (!vm->visu.active && vm->display.code & (1 << MSG_LIVE))
		ft_printf("\n%sPlayer %d (%s) is said to be alive%s",
				player->color.term,
				player->num * player->num_type,
				player->name,
				vm->color.off);
}

void		display_winner(t_vm *vm)
{
	if (vm->visu.active)
		return ;
	ft_printf("\n%sContestant %d, \"%s\", has won !\n%s",
			vm->winner->color.term,
			vm->winner->num * vm->winner->num_type,
			vm->winner->name,
			vm->color.off);
}
