/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/18 20:21:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		getval_mod(char *arena, int index, int nb_bytes, int mod)
{
	int	i;
	int val;

	i = -1;
	val = 0;
	ft_printf("getval mod, index = %d nbbytes = %d\n", index, nb_bytes);
	while (++i < nb_bytes)
	{
		ft_printf("getval mod: i = %d val = %d arena[index + i] = %d\n", i, val, arena[index + i]);
		val = val * 10 + arena[(index + i) % mod];
	}
	return (val);
}

/*
** store pointer on arg, loop to
** beginning if ptr located after mod len in arena
*/

int		getval_params(char *arena, t_instruction *ins, int i, int mod)
{
	int		j;
	t_parameter *param;

	j = -1;
	while (++j < ins->op.nb_params)
	{	
		param = &ins->params[j];
		if ( !(param->type & g_op_tab[ins->op.opcode - 1].arg_types[j]))
			return (-1);
		param->value = getval_mod(arena, i, param->nb_bytes, mod);
		i += param->nb_bytes;
		ft_printf("param value = %d\n", param->value);
		if (param->type == REG_CODE && param->value >= REG_NUMBER)
			return (-1);
	}
	return (0);
}

/*
** Check validity of parameters encoding byte, store type and in instruction
** structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

static int		is_valid_ocp(unsigned char hex, t_instruction *ins)
{
	static int		len[4] = {NA, E_REG, E_DIR, E_IND};
	int				t;
	int				arg;
	t_parameter		*param;

	arg = g_op_tab[ins->op.opcode - 1].nb_params;
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	if (hex & 3)
		return (0);
	while (--arg >= 0 && (t = -1))
	{
		while (++t < 3)
		{
			hex = hex >> 2;
			param = &ins->params[arg];
			if (g_op_tab[ins->op.opcode - 1].nb_params == 1)
			{
				param->type = g_op_tab[ins->op.opcode - 1].arg_types[0];
				param->nb_bytes = len[(int)param->type];
			}
			if ((int)((hex & 3)))
			{
				param->type = hex & 3;
				param->nb_bytes = len[hex & 3];
				if ((hex & 3) == DIR_CODE
					&& g_op_tab[ins->op.opcode - 1].describe_address == 1)
						param->nb_bytes = 2;
				break;
			}
		}
		if (!ins->params[arg].nb_bytes)
			return (0);
	}
	return (1);
}

/*
** Check validity of instruction at i (op, ocp, args), store op and ocp in instruction structure
** Return 0 if instruction is invalid (length of instruction if valid)
** Input: memory string, int starting point (i), structure to store instruction, int size
** beyond which index circles back
*/

int				get_instruction(char *arena, t_instruction *ins, int i, int mod)
{
	unsigned 	char	hex;
	int	len;

	ft_bzero((void *)ins, sizeof(t_instruction));
	hex = *(unsigned char *)(arena + (i % mod));
	if ((int)hex >= NB_INSTRUCTIONS || !hex)
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1], sizeof(t_op));
	++i;
	if (ins->op.has_ocp == OCP_YES)
	{
		ins->ocp = (unsigned char)*(arena + (i % mod));
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
		{
			ft_bzero((void *)ins, sizeof(*ins));
			return (0);
		}
	}
	if (getval_params(arena, ins, i + ins->op.has_ocp, mod) == -1)
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	len = ins->params[0].nb_bytes + ins->params[1].nb_bytes + ins->params[2].nb_bytes + ins->op.has_ocp + 1;
	return (len);

}

