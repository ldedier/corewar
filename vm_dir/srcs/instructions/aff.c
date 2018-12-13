/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c			                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 18:31:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Input: vm (for arena and player), proc (for register and pc),
** arg for X arg, 
** Returns 
*/

int		ins_aff(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	//penser a faire buffer comme doc au debut converse slack
	(void)vm;
	(void)proc;
	(void)arg;
	return (SUCCESS);
}
