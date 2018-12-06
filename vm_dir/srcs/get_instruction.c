/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 22:34:41 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			memmove_arg(char *arena, t_parameter *arg, int i, int mod)
{
	if (i + arg->nb_bytes < mod)
		ft_memmove((void *)&arg->value, (void *)(arena + i), arg->nb_bytes);
	else
	{
		ft_memmove((void *)&arg->value, (void *)(arena + i), MEM_SIZE - i);
		ft_memmove((void *)&arg->value, (void *)(arena + i),
				(i + arg->nb_bytes) % mod);
	}
	if (arg->type == REG_CODE && (arg->value >= REG_SIZE || arg->value < 0))
		return (0);
	return (arg->nb_bytes);
}

int		store_arg(char *arena, t_instruction *ins, int i, int mod)
{
	int	arg;
	int	start;

	arg = -1;
	start = i;
	while (++arg < ins->op.nb_params)
		if (!(i += memmove_arg(arena, &ins->params[arg], i, mod)))
			return (0);
	return (i - start);
}

/*
 ** Returns true if instruction includes parameter encoding byte, (else false)
 ** Input: opcode of instruction
 */

static int		needs_ocp(int op)
{
	return (op != LIVE && op != ZJMP && op != FORK && op != LFORK);
}

/*
 ** Checks validity of parameters encoding byte, stores in instruction structure
 ** handles exception when T_DIR > 2 bytes instead of 4
 */

static int		is_valid_ocp(char hex, t_instruction *ins)
{
	static int	type[3] = {REG_CODE, DIR_CODE, IND_CODE};
	static int	len[3] = {T_REG, T_DIR, T_IND};
	int			i;
	int			t;
	int			op;

	i = 0;
	if (!needs_ocp(op = ins->op.opcode))
		return (1);
	while (++i < 4)
	{
		t = -1;
		while (++t < 3 && !(ins->params[i].nb_bytes = 0))
			if (hex & (type[t] << (i + 2)))
			{
				if (g_op_tab[op].arg_types[t] & type[t])
				{
					ft_printf("param # %d : %d bytes\n", i, type[t]);
					ins->params[i].type = type[t];
					ins->params[i].nb_bytes = len[t];
					if (type[t] == T_DIR && g_op_tab[op].describe_address)
						ins->params[i].nb_bytes = 2;
				}
				else
					return (0);
			}
	}
	return (!(hex & 3));
}

/*
 ** Check validity of instruction at i, stores in instruction structure
 ** Return 0 if invalid instruction, length of instruction if valid
 ** Input: arena string, int starting point (i), structure to store instruction
 ** details, int size beyond which index circles back
 */

int				get_instruction(char *arena, t_instruction *ins, int i, int mod)
{
	char	hex;
	int		arglen;
	t_parameter	*arg;

	arg = ins->params;
	hex = *(arena + (i >= mod ? 0 : i));
	if (hex >= NB_INSTRUCTIONS || hex < 0)
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex], sizeof(t_op));
	hex = *(arena + ((i + 1) >= mod ? 1 : i + 1));
	if (!(ins->ocp = is_valid_ocp(hex, ins)))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	if (!(ins->params->nb_bytes = store_arg(arena, ins, i, ins->ocp)))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	//	ft_printf("valid opcode! = %d in index %d\n", ins->op.opcode, i);
	arglen = arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes;
	return (1 + needs_ocp(ins->op.opcode) + arglen);
}
