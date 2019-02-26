/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:27:27 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 21:45:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_colors(t_vm *vm)
{
	int i;
	static char *color_ref[4] = {COLF_BRED, COLF_BGREEN, COLF_BBLUE, COLF_BBROWN};

	i = -1;
	if (vm->visu.active)
		return ;
	while (++i < vm->nb_players)
		ft_memmove(vm->player[i].color.term, color_ref[i], 11);
	ft_memmove(vm->col.cycle, COL_CYCLES, 11);
	ft_memmove(vm->col.death, COL_DEATH, 11);
	ft_memmove(vm->col.resize, COL_RESIZE, 11);
}
