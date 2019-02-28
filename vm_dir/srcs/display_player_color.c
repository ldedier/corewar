/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:04:17 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 21:38:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_player_intro(t_player *player)
{
	ft_printf("\n%s* Player %d, weighing %d bytes, \"%s\" (\"%s\") !"EOC, player->color->value,

			player->num_type * player->num,
			player->algo_len,
			player->name,
			player->comm[0] ? player->comm : "");
}

void		display_player_alive(t_vm *vm, t_player *player)
{
	if (vm->display & (1 << MSG_LIVE))
		ft_printf("\nPlayer %d (%s) is said to be alive",
				player->num_type * player->num, player->name);
}

void		display_winner(t_vm *vm)
{
	ft_printf("\n%sContestant %d, ", vm->winner->color->value, -vm->winner->num);
	ft_putchar('"');
	ft_printf("%s", vm->winner->name);
	ft_putchar('"');
	ft_printf(", has won !\n"EOC);
}
