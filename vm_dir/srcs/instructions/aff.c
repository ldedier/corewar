/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:36:44 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/08 19:59:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Input: vm (for arena and player), proc (for register and pc),
** arg for X arg,
** Returns
*/

static void		output_aff(t_process *proc)
{
	if (proc->player->aff_buf[0])
	{
		ft_printf("Aff: [%s] (player %d).\n", proc->player->aff_buf,
			proc->player->num);
		free(proc->player->aff_buf);
	}
	proc->carry = 1;
}

int				ins_aff(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	char	*tmp;
	int		i;
	int		len;

	if (!vm->dump)
	{
		if ((proc->reg[arg[0].value - 1]) % 256 == 0)
			output_aff(proc);
		else
		{
			if (proc->player->aff_buf) // if else moche d'emma
				len = ft_strlen(proc->player->aff_buf);
			else
				len = 0;
			if (!len)
			{
				proc->player->aff_buf = ft_memalloc(sizeof(char) + 1);
				proc->player->aff_buf[0] = (proc->reg[arg[0].value - 1]) % 256;
			}
			else
			{
				tmp = ft_memalloc((size_t)len + 2);
				i = -1;
				while (++i < len)
					tmp[i] = proc->player->aff_buf[i];
				tmp[i] = (proc->reg[arg[0].value - 1]) % 256;
				free(proc->player->aff_buf);
				proc->player->aff_buf = tmp;
			}
		}
	}
	return (SUCCESS);
}
