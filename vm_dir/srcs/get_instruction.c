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

/*
** Check validity of arg against expected type, store pointer on arg, loop to
** beginning if ptr located after mod len in arena
** Return total length of instruction if valid args, else 0 
*/

int		set_arg_ptr(char *arena, t_instruction *ins, int i, int mod)
{
	int		j;
//	int		start;

	j = -1;
//	start = i;
	i += (1 + (ins->ocp ? 1 : 0));
	while (++j < ins->op.nb_params)
	{	
		if ( !(ins->params[j].type & g_op_tab[ins->op.opcode - 1].arg_types[j]))
			return (0);
		if (i < mod - 1)
			ins->params[j].ptr = (char *)(arena + i);
		else
			ins->params[j].ptr = (char *)arena;
//	if (ins->params[j].type == REG_CODE && ((char )*ins->params[j].ptr > REG_NUMBER
//					|| (char )*ins->params[j].ptr <= 0))
//{
//			ft_printf("wrong register number = %d\n", *ins->params[j].ptr);
//			return (0);
//}
//		ins->params->nb_bytes += ins->params[j].nb_bytes;
	}
	return (1);
}


/*
** Check validity of parameters encoding byte, store type and in instruction structure
** handles exception when T_DIR > 2 bytes instead of 4
** Return ocp if valid, 0 if invalid
*/

static int		is_valid_ocp(char hex, t_instruction *ins)
{
	static int	len[4] = {NA, REG_SIZE, DIR_SIZE, IND_SIZE};
	int			t;
	int			arg;

	arg = g_op_tab[ins->op.opcode - 1].nb_params;
	ft_bzero((void *)ins->params, sizeof(t_parameter) * 3);
	ins->params[0].nb_bytes = 0;
	ins->params[1].nb_bytes = 0;
	ins->params[2].nb_bytes = 0;
//	ft_printf("init ocp hex = %#x\n", (unsigned char)hex);
	if ((NEEDS_OCP & (1 << ins->op.opcode) )&& (hex & 3))
		return (0);
	while (--arg >= 0)
	{
		hex = hex >> 2;
		t = -1;
		while (++t < 3)
		{
			if (g_op_tab[ins->op.opcode - 1].nb_params == 1)
			{
				ins->params[arg].type = g_op_tab[ins->op.opcode - 1].arg_types[0];
//				ft_printf("ins params[%d].type = %d`\n", arg, ins->params[arg].type);
				ins->params[arg].nb_bytes = len[(int)ins->params[arg].type];
//				ft_printf("ins params[%d].bytes = %d`\n", arg, ins->params[arg].nb_bytes);

			}
			if ((int)((hex & 3)))
			{
				ins->params[arg].type = hex & 3;
//				ft_printf("ins params[%d].type = %d`\n", arg, ins->params[arg].type);
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
//	int	len;

	hex = *(arena + (i % mod));
	if (hex >= NB_INSTRUCTIONS || !hex)
		return (0);
	else
	{
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1], sizeof(t_op));
//		ft_printf("detected %d\n", ins->op.opcode);
	}
	ins->ocp = *(arena + ((i + 1) % mod));
	
	if (!is_valid_ocp(ins->ocp, ins))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	if (!(NEEDS_OCP & (1 << (ins->op.opcode))))
		ins->ocp = 0;
//	ft_printf("ocp = %#x nb bytes = %d\n", ins->ocp, ins->params->nb_bytes);
	if (!(set_arg_ptr(arena, ins, i, mod)))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	ft_printf("%svalid instruction >> %s%s\n", COLF_CYAN, ins->op.description, COLF_OFF);
//	ft_printf("NEEDS OCP = %#x 1 << opcode = %#x\n", NEEDS_OCP, 1 << (ins->op.opcode));
	int len = ins->params[0].nb_bytes + ins->params[1].nb_bytes + ins->params[2].nb_bytes + ((NEEDS_OCP & (1 << (ins->op.opcode))) ? 1 : 0) + 1;
	ft_printf("get instruciton ret len = %d\n", len);
//	ft_printf("in 0 = %d in 1 = %d in 2 = %d\n", ins->params[0].nb_bytes, ins->params[1].nb_bytes, ins->params[2].nb_bytes);
	return (len);

}
