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
	char	*tmp;
	int		i;
	int		len;
	if (!vm->dump)
	{
		len = ft_strlen(proc->player->aff_buf);
		if (!len)
		{
			proc->player->aff_buf = ft_memalloc(sizeof(char) + 1);
			proc->player->aff_buf[0] = (arg[0].value) % 256;
		}
		else
		{
				tmp = ft_memalloc((size_t)len + 2);
				i = -1;
				while (++i < len)
					tmp[i] = proc->player->aff_buf[i];
				tmp[i] = (arg[0].value) % 256;
				free(proc->player->aff_buf);
				proc->player->aff_buf = tmp;
		}
	}
	return (SUCCESS);
}
