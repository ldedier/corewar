/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/06 16:05:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
/*
static int		mod(int val, int max)
{
		return (val >= 0 ? val % max : max - 1 - ((-val - max) % max));
}
*/


int			getval_mod(char *arena, int index, int nb_bytes, int modulo)
{
	unsigned int	i;
	int				val;

	i = 0;
	val = 0;
	(void)modulo;
//	ft_printf("getval mod on %d bytes\n", nb_bytes);
	while (i < (unsigned int)nb_bytes)
	{
		val <<= 8;
//		ft_printf("index + i = %d\n", index + i);
	//	ft_printf("val = %#x index + i = %d (index + i) %% mod = %d arena[index + i] = %#x arena[(index + i) %% mod]\n", val, index + i, (index + i) % mod, arena[index + i] % mod, arena[(index + i) % mod]);

		if (!i)
//		ft_printf("mod %d\n", mod);
			val |= arena[(index + i) % modulo];
		else
			val |= (unsigned char)arena[(index + i) % modulo];
//			val |= arena[mod(index + i, modulo)];
//		else
//			val |= (unsigned char)arena[mod((index + i), modulo)];
//		ft_printf("index + i %% mod = %d | val = %#x\n", (index + i) % mod, val);
//	ft_printf("val = %#x\n", val);
		++i;
	}
//	val = (unsigned short)val;
//	ft_printf("val = %d\n", val);
	return (val);
}

int			invalid_param(int type, int op)
{
		if (op != LIVE && !(type & g_op_tab[op - 1].arg_types[0])
			&& !(type & g_op_tab[op - 1].arg_types[1])
			&& !(type & g_op_tab[op - 1].arg_types[2]))
			return (1);
		return (0);
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
//		if (ins->op.opcode == LD)
//		ft_printf("\nopcode= %d j = %d params j type = %#x, \ngoptab 0 = %d goptab 1 = %d goptab 2 = %d\n", ins->op.opcode, j, ins->params[j].type, g_op_tab[ins->op.opcode- 1].arg_types[0], g_op_tab[ins->op.opcode - 1].arg_types[1], g_op_tab[ins->op.opcode - 1].arg_types[2]);
		param = &ins->params[j];
		param->value = getval_mod(arena, i, param->nb_bytes, mod);
//		if (ins->op.opcode == LD)
//			ft_printf("j = %d type = %d bytes = %d params value = %d\n", j, param->type, param->nb_bytes, param->value);
		i += param->nb_bytes;
//		if (param->type > g_op_tab[ins->op.opcode - 1].arg_types[j] ||(!(param->type & g_op_tab[ins->op.opcode - 1].arg_types[j])))
//			&& !(param->type & g_op_tab[ins->op.opcode - 1].arg_types[1])
//			&& !(param->type & g_op_tab[ins->op.opcode - 1].arg_types[2])))
//		{
//			return (-1);
//			ft_printf("invalid params\n");
//			return (-1); // GROS GROS TEST
//		}
//		ft_printf("param->value = %d\n", param->value);
//		ft_printf("j = %d params[j].value = %d, type= %d\n",j, ins->params[j].value, ins->params[j].type);
//		ft_printf("param type = %d value = %d\n", param->type, param->value);
//		if (param->type == IND_CODE)
//		{
//			param->value %= IDX_MOD;
//			ft_printf("param value = %d\n", param->value);
//			if (param->value < 0)
//			{
//				param->value += IDX_MOD;
//				ft_printf("AFTER value = %d\n", param->value);
//			}
//		}
		if (!param->type || (param->type == T_REG && (param->value > REG_NUMBER || param->value <= 0))) // PEUT ETRE REMETTRE
		{
			return (-1);
		}
	}
	if (((ins->op.opcode == STI || ins->op.opcode == ST || ins->op.opcode == AFF) && ins->params[0].type != T_REG)
			|| ((ins->op.opcode == LD || ins->op.opcode == LLD) && (ins->params[1].type != T_REG /*|| ins->params[1].value == 1)*/))
			|| (ins->op.opcode >= ADD && ins->op.opcode <= XOR && (/*ins->params[0].type != T_REG || ins->params[1].type != T_REG ||*/ ins->params[2].type != T_REG))
			|| ((ins->op.opcode == LDI || ins->op.opcode == LLDI) && ins->params[2].type != T_REG))
		return (-1);
	return (0);
}

/*
** Check validity of parameters encoding byte, store type and in instruction
** structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

 int	is_valid_ocp(unsigned char hex, t_instruction *ins)
{
	static int		len[4] = {NA, E_REG, E_DIR, E_IND};
	int				arg;
	unsigned char	op;
	t_parameter		*param;

	arg = 3;
	op = hex;
//	ft_printf("hex = %#x hex & 3 = %#x\n", hex, hex & 3);
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	while (--arg >= 0)
	{
//		ft_printf("arg = %d\n", arg);
		param = &ins->params[arg];
		hex = hex >> 2;
		if (arg >= g_op_tab[ins->op.opcode - 1].nb_params)
			param->type = NA;
		else
		{
//			ft_printf("hex = %#x, hex & 3 = %#x\n", hex, hex & 3);
			param->type = (hex & 3);
			if (param->type >= 0 && param->type < 4)
				param->nb_bytes = len[(int)param->type];
//			ft_printf("type= %#x nb bytes= %d\n", param->type, param->nb_bytes);
			if (param->type == DIR_CODE)
				param->nb_bytes -=
					g_op_tab[ins->op.opcode - 1].describe_address * 2;
		}
	}
	if (!op /*|| op & 3*/)
		return (0);
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

	len = 0;
	hex = *(unsigned char *)(arena + (i % mod));
	if (!ins->op.opcode && ((int)hex > NB_INSTRUCTIONS || (int)hex == 0))
		return (0);
	++i;
		if (!ins->op.opcode)
		{
			ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1],
															sizeof(t_op));
		}
		ins->ocp = (unsigned char)*(arena + (i % mod));
	if (ins->op.has_ocp == OCP_YES)
	{
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
		{
			len = ins->params[0].nb_bytes + ins->params[1].nb_bytes +
			ins->params[2].nb_bytes + ins->op.has_ocp + 1;
			return (-len);
		}
	}
	else
	{
		if (ins->op.opcode != LIVE)
			ins->params[0].type = IND_CODE;
		else
			ins->params[0].type = g_op_tab[ins->op.opcode - 1].arg_types[0];
		ins->params[0].nb_bytes =
			4 - 2 * g_op_tab[ins->op.opcode - 1].describe_address;
	}
		len = ins->params[0].nb_bytes + ins->params[1].nb_bytes +
						ins->params[2].nb_bytes + ins->op.has_ocp + 1;
	if (getval_params(arena, ins, i + ins->op.has_ocp, mod) == -1)
	{
		return (-len);
	}
	return (len);
}
