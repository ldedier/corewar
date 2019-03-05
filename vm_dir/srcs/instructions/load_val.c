/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:29:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/30 18:34:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void	load_arena(t_vm *vm, t_process *proc, int index, int val)
{
	int 	i;
	int		mod_index;
	int		byte_val;

	i = -1;
	mod_index = mod(index, MEM_SIZE);
	while (++i < DIR_SIZE)
	{
		if (mod_index >= MEM_SIZE)
			mod_index -= MEM_SIZE;
		byte_val = val & (0xFF << ((3 - i) * 8));
		vm->arena[mod_index] = byte_val >> ((3 - i) * 8);
		vm->metarena[mod_index].color_index = proc->player->color.index;
		vm->metarena[mod_index].alt_color = ALT_COLOR_VALUE;
		++mod_index;
	}
}

void	load_reg(t_vm *vm, t_process *proc, int num, int val)
{
	(void)vm;
	proc->reg[num - 1] = val;
}
