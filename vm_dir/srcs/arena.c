/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/25 15:59:54 by emuckens         ###   ########.fr       */
/*   Updated: 2019/02/25 13:47:12 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void			update_buttons(t_vm *vm)
{
	if (vm->nb_players)
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 1;
	else
		vm->visu.buttons[CLEAN_ARENA_BUTTON].enabled = 0;
}

/*
** dump is called in every cycle to check if we have reached the max cycle
** amount set by the [-dump] option
*/

void			dump(t_vm *vm)
{
	int		i;
	int		hex;

	if (vm->total_cycle >= vm->dump)
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
		exit(1);
	}
}
