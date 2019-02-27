/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:04:17 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/27 15:07:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_player_intro(t_vm *vm, t_player *player)
{
	if (vm->visu.active)
		return ;
	ft_printf("%s\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !"EOC,
			player->color.term,
			player->num_type * player->num,
			player->algo_len,
			player->name,
			player->comm[0] ? player->comm : "");
}

void		display_player_alive(t_vm *vm, t_player *player)
{
	if (!vm->visu.active && vm->display & (1 << MSG_LIVE))
		ft_printf("%s\nPlayer %d (%s) is said to be alive"EOC,
				player->color.term, player->num_type * player->num, player->name);
}

void		display_winner(t_vm *vm)
{
	if (vm->visu.active)
		return ;
	ft_printf("%s\nContestant %d, ", vm->winner->color.term, -vm->winner->num);
	ft_putchar('"');
	ft_printf("%s", vm->winner->name);
	ft_putchar('"');
	ft_printf(", has won !\n"EOC);
}
