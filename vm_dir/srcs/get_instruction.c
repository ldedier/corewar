/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 16:54:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		is_valid_opcode(char hex)
{
	if (hex >= NB_INSTRUCTIONS)
		ft_printf("invalid opcode!\n");
	return (hex < NB_INSTRUCTIONS);
}

static int		needs_ocp(int op)
{
	return (op != LIVE && op != ZJMP && op != FORK && op != LFORK);
}

static int		is_valid_ocp(char hex, t_instruction *ins)
{
	int	type[3] = {1, 10, 11};
	int i = -1;
	int	t = 0;

	while (++i < 4 && (t = -1))
		while (++t < 3)
		{
			if (hex & (type[t] << (i + i)))
			{
				hex ^= (type[t] << (i + i));
				ins->params[i].nb_bytes = ft_pow(2, i);
			}
			else
				ins->params[i].nb_bytes = 0;
		}
	return (!(needs_ocp(ins->op.opcode) && hex));
}

int				get_instruction(char *arena, t_op *tab, int i, t_instruction *ins)
{
	char	hex;
	int		arglen;
	t_parameter	*arg;
	int		ret;


	hex = *(arena + (i >= MEM_SIZE ? 0 : i));
	if (!(ret = is_valid_opcode(hex)))
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&tab[ret], sizeof(t_op));
	hex = *(arena + ((unsigned int)(i + 1) >= MEM_SIZE ? 1 : i + 1));
	if (!(ins->ocp = is_valid_ocp(hex, ins)))
		return (0);
	if (!(ins->params->nb_bytes = store_arg(arena, ins, i, ins->ocp)))
		return (0);
	ft_printf("valid opcode! = %d in index %d\n", ins->op.opcode, i);
	arg = ins->params;
	arglen = arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes;
	return (1 + needs_ocp(ins->op.opcode) + arglen);
}
