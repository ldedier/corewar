/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction_nostore.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 17:44:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** Check validity of parameters encoding byte, store type and in instruction
** structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

 int	is_valid_ocp_nostore(unsigned char hex, t_instruction *ins)
{
	int				arg;
	unsigned char	op;
	t_parameter		*param;

	arg = 3;
	op = hex;	
	if (op & 0x3)
		return (0);	
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	while (--arg >= 0 && (hex = hex >> 2) >= 0)
	{
		param = &ins->params[arg];
		if ((param->type = hex & 3) >= 0 && !(param->type & ins->op->arg_types[arg]))
			return (0);
	}
	return ((op));
}

/*
** Checks validity of instruction at i (op, ocp, args), stores op and ocp
** in instruction structure
** Return 0 if instruction is invalid (length of instruction if valid)
** Input: memory string, int starting point (i), struct. to store instruction,
** int size beyond which index circles back
*/

int			get_ins_nostore(char *arena, t_instruction *ins,
											unsigned int i, unsigned int mod)
{
	unsigned char	hex;
	int				len;

	len = 0;
	hex = *(unsigned char *)(arena + i);
	if ((int)hex > NB_INSTRUCTIONS || (int)hex == 0)
		return (0);
	if (++i == mod)
		i -= mod;
	ins->op = &g_op_tab[(int)hex - 1];
	ins->ocp = (unsigned char)*(arena + i);
	if (ins->op->has_ocp == OCP_YES)
	{
		if (!is_valid_ocp_nostore((unsigned char)ins->ocp, ins))
			return (-1);
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
	return (1);
}

