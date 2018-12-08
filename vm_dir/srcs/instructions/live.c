/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/05 16:08:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ins_live(t_vm *vm,t_parameter arg[3], int pl)
{
	(void)pl;
	if (arg[FIRST].value >= MAX_PLAYERS)
		return (FAILURE);
	vm->proc[arg[FIRST].value].live = 1;
	vm->live.last_pl = arg[FIRST].value;
	++vm->live.nb;
	if (!vm->proc[arg[FIRST].value].live)
		++vm->live.total_pl;
	return (SUCCESS);
}
