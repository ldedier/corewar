/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 21:41:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:04:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_live_sum(t_vm *vm)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			res += vm->player[i].live;
		i++;
	}
	return (res);
}
