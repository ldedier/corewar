/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/10/31 17:46:43 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
**init_vm function initializes our corewar VM's environment by setting all
**its parameters to their default value.
*/

void		init_vm(t_vm *vm, char **argv)
{
	int i;

	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].hex = 0;
		i++;
	}
}
