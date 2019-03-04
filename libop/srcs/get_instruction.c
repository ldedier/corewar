/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/04 15:28:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			getval_mod(char *arena, int index, int nb_bytes, int modulo)
{
	unsigned int	i;
	int				val;

	i = 0;
	val = 0;
//	ft_printf("src = %s\n", arena);
	val |= arena[(index + i) % modulo];
//	ft_printf("intermediate val = %d\n", val);
	while (++i < (unsigned int)nb_bytes) // avant <
	{
		val <<= 8;
		val |= (unsigned char)arena[(index + i) % modulo];
//		ft_printf("intermediate val = %d\n", val);
	}
	return (val);
}

/*
** store pointer on arg, loop to
** beginning if ptr located after mod len in arena
*/

int			getval_params(char *arena, t_instruction *ins, int i, int mod)
{
	int			j;
	t_parameter	*param;
	int			op;

	j = -1;
	op = ins->op->opcode;
	while (++j < ins->op->nb_params)
	{
		param = &ins->params[j];
		param->value = getval_mod(arena, i, param->nb_bytes, mod);
		i += param->nb_bytes;
		if (!param->type
			|| (param->type == T_REG
				&& (param->value > REG_NUMBER || param->value <= 0)))
			return (-1);
	}
	if ((ins->params[0].type != T_REG
			&& (op == STI || op == ST || op == AFF))
			|| ((op == LD || op == LLD) && ins->params[1].type != T_REG)
			|| (op >= ADD && op <= XOR && ins->params[2].type != T_REG)
			|| (op >= ADD && op <= SUB && ins->params[2].type != T_REG)
			|| ((op == LDI || op == LLDI) && ins->params[2].type != T_REG))
		return (-1);
	return (0);
}


/*
** Check validity of parameters encoding byte, store type and in instruction
** structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

int			is_valid_ocp(unsigned char hex, t_instruction *ins)
{
	static int		len[4] = {NA, E_REG, E_DIR, E_IND};
	int				arg;
	unsigned char	op;
	t_parameter		*param;

	arg = 3;
	op = hex;

	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	while (--arg >= 0 && (hex = hex >> 2) >= 0)
	{
		param = &ins->params[arg];
		if ((param->type = hex & 3) >= 0 && param->type < 4)
			param->nb_bytes = len[(int)param->type];
		if (param->type == DIR_CODE)
			param->nb_bytes -=
					g_op_tab[ins->op->opcode - 1].describe_address * 2;
		if (arg >= g_op_tab[ins->op->opcode - 1].nb_params)
		{
			param->type = NA;
			param->nb_bytes = 0;
		}
	}
	if (ins->op->opcode == ST || ins->op->opcode == STI) // pas tres coherent de mettre juste ST, pas LD ou LLD en gestion 3e argument attendu vu le ocp
		if (op & 0x3)
			return (0);
	return ((op));
}

/*
** Checks validity of instruction at i (op, ocp, args), stores op and ocp
** in instruction structure
** Return 0 if instruction is invalid (length of instruction if valid)
** Input: memory string, int starting point (i), struct. to store instruction,
** int size beyond which index circles back
*/

int			get_ins(char *arena, t_instruction *ins,
											unsigned int i, unsigned int mod)
{
	unsigned char	hex;
	int				len;

	len = 0;
	hex = *(unsigned char *)(arena + i);
//	ft_printf("i = %zu hex = %d\n", i, hex);
	if (++i == mod)
		i -= mod;
	if (!ins->op && (((int)hex > NB_INSTRUCTIONS) || (int)hex == 0))
	{
//		ft_printf("mauvais op\n");
		return (0);
	}
	if (!ins->op)
		ins->op = &g_op_tab[(int)hex - 1];
	ins->ocp = (unsigned char)*(arena + i);
//	ft_printf("op = %d ocp = %#x\n", ins->op->opcode, ins->ocp);
	if (ins->op->has_ocp == OCP_YES)
	{
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
		{
//			ft_printf("invalid ocp\n");
			len = ins->params[0].nb_bytes + ins->params[1].nb_bytes +
			ins->params[2].nb_bytes + ins->op->has_ocp + 1;
			return (-len);
		}
	}
	else
	{
		if (ins->op->opcode != LIVE)
			ins->params[0].type = IND_CODE;
		else
			ins->params[0].type = g_op_tab[ins->op->opcode - 1].arg_types[0];
		ins->params[0].nb_bytes = 4
			- 2 * g_op_tab[ins->op->opcode - 1].describe_address;
	}
	len = ins->params[0].nb_bytes + ins->params[1].nb_bytes +
						ins->params[2].nb_bytes + ins->op->has_ocp + 1;
	if (getval_params(arena, ins, i + ins->op->has_ocp, mod) == -1)
	{
//			ft_printf("invalid params\n");
		return (-len);
	}
	return (len);
}
