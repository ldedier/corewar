/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:21:03 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 17:21:24 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lives_turn(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("%s %d", MSG_NBR_LIVES_TURN, vm->live.total_pl);
	ft_printf(" %s %d\n", MSG_RESIZE, vm->c_to_die);
}

void	cycles_to_autoresize(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("%d %s\n", vm->checks - 1, MSG_NBR_TO_AUTORESIZE);
}

void	resize(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("%s %d\n", MSG_RESIZE, vm->c_to_die);
}
