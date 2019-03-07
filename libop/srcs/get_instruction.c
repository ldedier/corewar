/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/07 16:36:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			getval_mod(char *arena, int index, int nb_bytes, int modulo)
{
	unsigned int	i;
	int				val;

	i = 0;
	val = 0;
	val |= arena[(index + i) % modulo];
	while (++i < (unsigned int)nb_bytes)
	{
		val <<= 8;
		val |= (unsigned char)arena[(index + i) % modulo];
	}
	return (val);
}

static int	valid_params(t_instruction *ins)
{
	int		op;

	op = ins->op->opcode;
	if (((op == LD || op == LLD) && ins->params[1].type != T_REG)
		|| (op >= ADD && op <= XOR && ins->params[2].type != T_REG)
		|| (op >= ADD && op <= SUB && ins->params[2].type != T_REG)
		|| ((op == LDI || op == LLDI) && ins->params[2].type != T_REG)
		|| (ins->params[0].type != T_REG
			&& (op == STI || op == ST || op == AFF)))
		return (0);
	return (1);
}

/*
** store pointer on arg, loop to
** beginning if ptr located after mod len in arena
*/

int			getval_params(char *arena, t_instruction *ins, int i, int mod)
{
	int			j;
	t_parameter	*param;

	j = -1;
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
	if (!valid_params(ins))
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
	while (--arg >= 0 && (hex = hex >> 2) >= 0)
	{
		param = &ins->params[arg];
		if ((param->type = hex & 3) >= 0 && param->type < 4)
			param->nb_bytes = len[(int)param->type];
		if (param->type == DIR_CODE)
			param->nb_bytes -= ins->op->describe_address * 2;
		if (arg >= g_op_tab[ins->op->opcode - 1].nb_params)
			ft_bzero(param, sizeof(t_parameter));
	}
	return ((op));
}

int			get_bytelen(t_instruction *ins)
{
	int len;
	int	i;

	len = 1 + ins->op->has_ocp;
	i = -1;
	while (++i < 3)
		len += ins->params[i].nb_bytes;
	return (len);
}

/*
** Checks validity of instruction at i (op, ocp, args), stores op and ocp
** in instruction structure
** Return 0 if instruction is invalid (length of instruction if valid)
** Input: memory string, int starting point (i), struct. to store instruction,
** int size beyond which index circles back
*/

int			get_ins(char *arena, t_instruction *ins,
											unsigned int i, int store)
{
	unsigned char	hex;

	hex = *(unsigned char *)(arena + i++);
	i -= (i == MEM_SIZE ? MEM_SIZE : 0);
	if (!ins->op)
	{
		if ((int)hex > NB_INSTRUCTIONS || (int)hex == 0)
			return (0);
		ins->op = &g_op_tab[(int)hex - 1];
	}
	ins->ocp = (unsigned char)*(arena + i);
	if (ins->op->has_ocp == OCP_YES)
	{
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
			return (0);
//			return (-get_bytelen(ins));
	}
	else
	{
		ins->params[0].type = ins->op->arg_types[0];
		ins->params[0].nb_bytes = 4 - 2 * ins->op->describe_address;
	}
	if (store && getval_params(arena, ins, i + ins->op->has_ocp, MEM_SIZE))
		return (1 + ins->op->has_ocp);
//		return (-get_bytelen(ins));
	return (get_bytelen(ins));
}
