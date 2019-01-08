/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_turn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:21:37 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 17:23:22 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	last_live(t_vm *vm, t_process *proc)
{
	(void)vm;
	(void)proc;
//	ft_printf(">>> %d [ %s ]", proc->player->num, proc->player->name);
}

void	cycle_end(t_vm *vm, t_process *proc)
{
	(void)proc;
	(void)vm;
	ft_printf("\n%s | ", MSG_CYCLE_END);
}

void	move_one(t_vm *vm, t_process *proc)
{
	(void)vm;
	(void)proc;
	ft_printf("%-*s ", PAD_INS, MSG_MOVE_ONE);
}

void	cycle_nb(t_vm *vm, t_process *proc)
{
	(void)proc;
	(void)vm;
//	ft_printf("\n%s%s [ %d ] %s\n", COLF_BGREY,
//			MSG_CYCLES_REMAINING, CYCLE_TO_DIE - vm->cycle, COLF_OFF);
}

void	turn_player(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("PLAYER %-*d aka %-*s", PAD_PLNUM, proc->player->num,
			PAD_PLNAME, proc->player->name);
}
