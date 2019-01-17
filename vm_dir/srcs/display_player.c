/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:19:41 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 17:20:38 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	pl_death(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("Process belonging to %d (%s)  %s\n", proc->player->num,
																								proc->player->name, MSG_DEATH);
}

void	pl_live(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf(" >>>%s", proc->player->num);
}

void	pl_victory(t_vm *vm, t_process *proc)
{
	(void)vm;
	(void)proc;
	ft_printf("%s %s %d [%s] \n", MSG_VICTORY, LABEL_PLAYER, vm->winner->num,
																								vm->winner->name);
}

void	pl_cycle(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf(".... %d", proc->pending.cycles);
}

void	pl_pc(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("[%d]", proc->pc);
}
