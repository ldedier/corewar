/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:40:29 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/04 20:08:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		isvalid_op(unsigned char op)
{
	return (op > 0 && op <= 16);
}

static int		isvalid_ocp(t_instruction *ins, unsigned char op, unsigned char ocp)
{
	int i;
	int	j;
	int	offset;
	int ret;
	static int	len[4] = {NA, E_REG, E_DIR, E_IND};

	i = -1;
	offset = 0xc0;
	ins->params[0].type = 0;
	ins->params[1].type = 0;
	ins->params[2].type = 0;
	while (++i < g_op_tab[(int)(op - 1)].nb_params)
	{
		ins->params[i].type = ((ocp & offset) >> (6 - i * 2));
		j = -1;
	   while (++j < ins->op->nb_params)
	   {
		   if ((ins->params[i].type << (j * 2) & ins->op->arg_types[i]))
			   break;
	   }
	   if (j == ins->op->nb_params)
		   return (0);
	   ins->params[i].nb_bytes = len[(int)ins->params[i].type];
	   if (ins->params[i].type == DIR_CODE)
		   ins->params[i].nb_bytes -= (ins->op->describe_address * 2);
	   offset = offset >> 2;
	}
	if (g_op_tab[op - 1].has_ocp && (ret = (ins->ocp - (ins->params[0].type << 6) - (ins->params[1].type << 4) - (ins->params[2].type << 2))))
		return (0);
	return (1);
}

int			read_ins(char *src, t_instruction *ins, unsigned int *index, unsigned int mod)
{
	unsigned char	op;
	int				i;

	if (isvalid_op((op = *(src + *index))))
		ins->op = &g_op_tab[op - 1];
	else
		return (0);
	if (++(*index) == MEM_SIZE)
		*index -= MEM_SIZE;
	if (ins->op->has_ocp)
	{
		if (!(ins->ocp = *(src + *index)) || !isvalid_ocp(ins, ins->op->opcode, ins->ocp))
			return (0);
		if (++(*index) == MEM_SIZE)
			*index -= MEM_SIZE;
	}
	else
	{
		ins->params[0].type = DIR_CODE;
		ins->params[0].nb_bytes = 4 - 2 * ins->op->describe_address;
	}
	i = -1;
	while (++i < ins->op->nb_params)
	{
		ins->params[i].value = getval_mod(src, *index, ins->params[i].nb_bytes, mod);
		if (!ins->params[i].type
				|| (ins->params[i].type == T_REG && !(ins->params[i].value > 0 && ins->params[i].value <= 16)))
			return (0);
		if (((*index) += ins->params[i].nb_bytes) >= MEM_SIZE)
			*index -= MEM_SIZE;
	}
	return (1);
}
