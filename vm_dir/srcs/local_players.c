/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:53:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/16 13:57:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_local_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->local_player[i] = vm->player[i];
		vm->local_player[i].color.value = NULL;
		vm->local_player[i].num = vm->nb;
		i++;
	}
}
