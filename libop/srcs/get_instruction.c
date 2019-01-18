/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/18 17:49:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			getval_mod(char *arena, int index, int nb_bytes, int mod)
{
	unsigned int	i;
	int				val;

	i = 0;
	val = 0;
	while (i < (unsigned int)nb_bytes)
	{
//		ft_printf("index = %d i = %d val = %d\n", index, i, val);
		val <<= 8;
		val |= (unsigned char)arena[(index + i) % mod];
//		ft_printf("after i = %d val = %d\n", i, val);
		++i;
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

	j = -1;
	while (++j < ins->op.nb_params)
	{
//		ft_printf("opcode= %d j = %d params j type = %#x, goptab 0 = %d goptab 1 = %d goptab 2 = %d\n", ins->op.opcode, j, ins->params[j].type, g_op_tab[ins->op.opcode- 1].arg_types[0], g_op_tab[ins->op.opcode - 1].arg_types[1], g_op_tab[ins->op.opcode - 1].arg_types[2]);
		param = &ins->params[j];
		if (!(param->type & g_op_tab[ins->op.opcode - 1].arg_types[0])
			&& !(param->type & g_op_tab[ins->op.opcode - 1].arg_types[1])
			&& !(param->type & g_op_tab[ins->op.opcode - 1].arg_types[2]))
		{
			return (-1);
		}
		param->value = getval_mod(arena, i, param->nb_bytes, mod);
//		ft_printf("j = %d params[j].value = %d, type= %#x\n",j, ins->params[j].value, ins->params[j].type);
		i += param->nb_bytes;
		if (param->type == REG_CODE && param->value > REG_NUMBER)
		{
			return (-1);
		}
	}
	return (0);
}

/*
** Check validity of parameters encoding byte, store type and in instruction
** structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

static int	is_valid_ocp(unsigned char hex, t_instruction *ins)
{
	static int		len[4] = {NA, E_REG, E_DIR, E_IND};
	int				arg;
	t_parameter		*param;

	arg = 3;
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	if (hex & 3)
		return (0);
	while (--arg >= 0)
	{
		param = &ins->params[arg];
		hex = hex >> 2;
		if (arg >= g_op_tab[ins->op.opcode - 1].nb_params)
			param->type = NA;
		else
		{
//			ft_printf("hex = %#x, hex & 3 = %#x\n", hex, hex & 3);
			param->type = (hex & 3);
			param->nb_bytes = len[(int)param->type];
//			ft_printf("type= %#x nb bytes= %d\n", param->type, param->nb_bytes);
			if (param->type == DIR_CODE)
				param->nb_bytes -=
					g_op_tab[ins->op.opcode - 1].describe_address * 2;
		}
	}
	return (1);
}

/*
** Checks validity of instruction at i (op, ocp, args), stores op and ocp
** in instruction structure
** Return 0 if instruction is invalid (length of instruction if valid)
** Input: memory string, int starting point (i), struct. to store instruction,
** int size beyond which index circles back
*/

int			get_instruction(char *arena, t_instruction *ins,
													unsigned int i, int mod)
{
	unsigned char	hex;
	int				len;

//	ft_bzero((void *)ins, sizeof(t_instruction));
//	ft_printf("ins address = %d\n", ins);
	hex = *(unsigned char *)(arena + (i % mod));
	ins->op.nb_params = 1;
	if ((int)hex > NB_INSTRUCTIONS || !hex)
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1],
															sizeof(t_op));
	++i;
//	ft_printf("considering instruction # %d\n", hex);
	if (ins->op.has_ocp == OCP_YES)
	{
		ins->ocp = (unsigned char)*(arena + (i % mod));
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
		{
			ft_bzero((void *)ins, sizeof(*ins));
			return (0);
		}
	}
	else
	{
		ins->params[0].type = g_op_tab[ins->op.opcode - 1].arg_types[0];
		ins->params[0].nb_bytes =
			4 - 2 * g_op_tab[ins->op.opcode - 1].describe_address;
	}
//	ft_printf("ocp is valid, = %#x\n", (unsigned char)ins->ocp);
	if (getval_params(arena, ins, i + ins->op.has_ocp, mod) == -1)
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	len = ins->params[0].nb_bytes + ins->params[1].nb_bytes +
						ins->params[2].nb_bytes + ins->op.has_ocp + 1;
//	ft_printf("instruction len = %d\n", len);
	return (len);
}
