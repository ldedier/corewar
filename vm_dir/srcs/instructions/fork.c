/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/07 19:23:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Input: vm (for arena and player), proc (for register and pc),
** arg for X arg
*/

int		ins_fork(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	(void)vm;
	(void)proc;
	(void)arg;
	++proc->player->nb_proc;
	return (SUCCESS);
}
