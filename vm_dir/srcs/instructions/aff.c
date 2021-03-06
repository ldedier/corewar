/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:36:44 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/11 18:28:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** [aff] instruction allows users to output characters to taunt other players
** by printing the character given by [arg 1] (% 256).
**
** This version includes a bonus: instead of only outputting the character
** every time [aff] is called, it stores the character inside a string and
** outputs the entire string when it's called with the value 0, thus allowing
** players to output entire strings (much more useful).
*/

static void		output_aff(t_process *proc)
{
	int len;

	if (proc->player->aff_buf[0])
	{
		ft_printf("\nAff: [%s] by player %d (\"%s\").", proc->player->aff_buf,
			proc->player->num, proc->player->name);
		len = ft_strlen(proc->player->aff_buf);
		ft_bzero(proc->player->aff_buf, (size_t)len);
	}
}

int				ins_aff(t_vm *vm, t_process *proc, t_parameter arg[3])
{
	int		i;

	if (vm->dump < 0 && !vm->visu.active)
	{
		if ((proc->reg[arg[0].value - 1]) % 256 == 0)
			output_aff(proc);
		else
		{
			i = 0;
			while (proc->player->aff_buf[i] && i < MAX_AFF_LEN)
				i++;
			if (i == MAX_AFF_LEN)
			{
				proc->player->aff_buf[i] = 0;
				output_aff(proc);
				proc->player->aff_buf[0] = (proc->reg[arg[0].value - 1]) % 256;
			}
			else
				proc->player->aff_buf[i] = (proc->reg[arg[0].value - 1]) % 256;
			if (vm->display.code & (1 << MSG_AFF))
				ft_printf("\nAff: %c");
		}
	}
	return (SUCCESS);
}
