/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:22:56 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 21:48:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [st] instruction loads value from register [arg 1] to the arena at the
** address [arg 2].
**
** Takes 2 arguments : first one necessarily a REGISTER
*/

int		ins_st(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	ft_printf("INS ST\n");
	getval_param_dest(vm, proc, &arg[0], 1);
	arg[1].value %= IDX_MOD;
	loadval(vm, proc, &arg[1], arg[0].dest_value);
	return (SUCCESS);
}
