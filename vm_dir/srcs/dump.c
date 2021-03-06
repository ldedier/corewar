/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:15:26 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 14:06:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** dump is called in every cycle to check if we have reached the max cycle
** amount set by the [-dump] option
*/

void		dump(t_vm *vm)
{
	int		i;
	int		hex;

	if (vm->dump >= 0 && vm->total_cycle >= vm->dump)
	{
		ft_putchar('\n');
		hex = 0;
		i = 0;
		while (i < MEM_SIZE)
		{
			if (i % 64 == 0)
				ft_printf("0x%04x : ", hex);
			ft_printf("%02x ", 0xFF & vm->arena[i]);
			if (((i + 1) % 64) == 0)
			{
				ft_printf("\n");
				hex += 64;
			}
			i++;
		}
		clear_vm(vm);
		exit(1);
	}
}
