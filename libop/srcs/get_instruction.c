/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:33:31 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/15 21:13:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** store pointer on arg, loop to
** beginning if ptr located after mod len in arena
*/

int		set_arg_ptr(char *arena, t_instruction *ins, int i, int mod)
{
	int		j;
	int		k;

	j = -1;
	while (++j < ins->op.nb_params)
	{	
		if ( !(ins->params[j].type & g_op_tab[ins->op.opcode - 1].arg_types[j]))
			return (-1);
		ins->params[j].ptr = (char *)(arena + i);
		ins->params[j].value = 0;
		k = -1;
		while (++k < ins->params[j].nb_bytes)
		{
			ins->params[j].value = ins->params[j].value << 8;
			ins->params[j].value += arena[(i + 1) % mod];
			++i;
		}
	}
//		ft_printf("arg1 = %#x arg2 = %#x arg3 = %#x\n", ins->params[0].value, ins->params[1].value, ins->params[2].value);
	return (i);
}

/*
** Check validity of parameters encoding byte, store type and in instruction structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return 1 if valid, 0 if invalid
*/

static int		is_valid_ocp(unsigned char hex, t_instruction *ins)
{
	static int	len[4] = {NA, E_REG, E_DIR, E_IND};
	int			t;
	int			arg;

//	ft_printf("opc = %#x\n", (unsigned char)hex);
	arg = g_op_tab[ins->op.opcode - 1].nb_params;
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	if (hex & 3)
		return (0);
	while (--arg >= 0)
	{
		t = -1;
		while (++t < 3)
		{
			hex = hex >> 2;
			if (g_op_tab[ins->op.opcode - 1].nb_params == 1)
			{
				ins->params[arg].type = g_op_tab[ins->op.opcode - 1].arg_types[0];
				ins->params[arg].nb_bytes = len[(int)ins->params[arg].type];
			}
			if ((int)((hex & 3)))
			{
				
				ins->params[arg].type = hex & 3;
				ins->params[arg].nb_bytes = len[hex & 3];
				if ((hex & 3) == DIR_CODE
					&& g_op_tab[ins->op.opcode - 1].describe_address == 1)
						ins->params[arg].nb_bytes = 2;
				t = 2;
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
	{
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1], sizeof(t_op));
		ft_printf("detected %d\n", ins->op.opcode);
	}
	if (ins->op.has_ocp == OCP_YES)
	{
		ins->ocp = (unsigned char)*(arena + ((i + 1) % mod));
		if (!is_valid_ocp((unsigned char)ins->ocp, ins))
		{
			ft_bzero((void *)ins, sizeof(*ins));
			return (0);
		}
	}
	if (set_arg_ptr(arena, ins, i + ins->op.has_ocp, mod) == -1)
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	ft_printf("has ocp = %d\n", ins->op.has_ocp);
	len = ins->params[0].nb_bytes + ins->params[1].nb_bytes + ins->params[2].nb_bytes + ins->op.has_ocp + 1;
	return (len);

}
