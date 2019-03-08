/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:40:29 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 17:11:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int		isvalid_op(unsigned char op)
{
	return (op > 0 && op <= 16);
}

static void		reset_type(t_instruction *ins)
{
	ins->params[0].type = 0;
	ins->params[1].type = 0;
	ins->params[2].type = 0;
}

static int		isvalid_ocp(t_instruction *ins, unsigned char op,
					unsigned char ocp)
{
	int			i;
	int			j;
	int			offset;
	static int	len[4] = {NA, E_REG, E_DIR, E_IND};

	i = -1;
	offset = 0xc0;
	reset_type(ins);
	while (++i < g_op_tab[(int)(op - 1)].nb_params && (j = -1))
	{
		ins->params[i].type = ((ocp & offset) >> (6 - i * 2));
		while (++j < ins->op->nb_params)
			if ((ins->params[i].type << (j * 2) & ins->op->arg_types[i]))
				break ;
		if (j == ins->op->nb_params)
			return (0);
		ins->params[i].nb_bytes = len[(int)ins->params[i].type];
		if ((offset = offset >> 2) && ins->params[i].type == DIR_CODE)
			ins->params[i].nb_bytes -= (ins->op->describe_address * 2);
	}
	if (g_op_tab[op - 1].has_ocp
			&& (ins->ocp - (ins->params[0].type << 6)
				- (ins->params[1].type << 4) - (ins->params[2].type << 2)))
		return (0);
	return (1);
}

static int		get_params(char *src, t_instruction *ins,
					unsigned int *j, int mod)
{
	int		i;

	i = -1;
	while (++i < ins->op->nb_params)
	{
		ins->params[i].value = getval_mod(src, *j, ins->params[i].nb_bytes,
			mod);
		if (!ins->params[i].type
			|| (ins->params[i].type == T_REG
				&& !(ins->params[i].value > 0 && ins->params[i].value <= 16)))
			return (0);
		if (((*j) += ins->params[i].nb_bytes) >= MEM_SIZE)
			*j -= MEM_SIZE;
	}
	return (1);
}

int				read_ins(char *src, t_instruction *ins, unsigned int *index,
					unsigned int mod)
{
	unsigned char	op;

	op = *(src + (*index));
	if (isvalid_op(op))
		ins->op = &g_op_tab[op - 1];
	else
		return (0);
	if (++(*index) == MEM_SIZE)
		*index -= MEM_SIZE;
	if (ins->op->has_ocp)
	{
		if (!(ins->ocp = *(src + *index))
				|| !isvalid_ocp(ins, ins->op->opcode, ins->ocp))
			return (0);
		if (++(*index) == MEM_SIZE)
			*index -= MEM_SIZE;
	}
	else
	{
		ins->params[0].type = DIR_CODE;
		ins->params[0].nb_bytes = 4 - 2 * ins->op->describe_address;
	}
	if (get_params(src, ins, index, mod) == -1)
		return (0);
	return (1);
}
