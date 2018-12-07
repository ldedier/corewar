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
static int			memmove_arg(char *arena, t_parameter *arg, int i, int mod)
{
	(void)mod;
	if (i < MEM_SIZE - 1)
		arg->ptr = (char *)(arena + i);
	else
		arg->ptr = (char *)arena;
	if (arg->type == REG_CODE && ((char)*(arg->ptr) >= REG_NUMBER || (char)*(arg->ptr) < 0))
		return (0);
	return (1);
}
*/
/*
 ** Returns true if instruction includes parameter encoding byte, (else false)
 ** Input: opcode of instruction
 */

static int		needs_ocp(int op)
{
	return (op != LIVE && op != ZJMP && op != FORK && op != LFORK);
}

int		store_arg(char *arena, t_instruction *ins, int i, int mod)
{
	int		j;
	int		start;
//	t_parameter	arg;

	j = -1;
	start = i;
	i += (1 + (ins->ocp ? 1 : 0));
	while (++j < ins->op.nb_params)
	{	
//		arg = ins->params[j];
		ft_printf("after len param j = %d\n", ins->params[j].nb_bytes);
		if (i < mod - 1)
			ins->params[j].ptr = (char *)(arena + i);
		else
			ins->params[j].ptr = (char *)arena;
	if (ins->params[j].type == REG_CODE && ((char )*ins->params[j].ptr > REG_NUMBER
					|| (char )*ins->params[j].ptr <= 0))
		{
			ft_printf("Invalid registre number\n");
			return (0);
		}
//		memmove_arg(arena, &ins->params[j], i, mod))
		i += ins->params[j].nb_bytes;
//		ft_printf("i = %d\n", i);

	}
	return (i - start - 1);
}


/*
 ** Checks validity of parameters encoding byte, stores in instruction structure
 ** handles exception when T_DIR > 2 bytes instead of 4
 */

static int		is_valid_ocp(char hex, t_instruction *ins)
{
	static int	type[3] = {REG_CODE, DIR_CODE, IND_CODE};
	static int	len[4] = {NA, REG_SIZE, DIR_SIZE, IND_SIZE};
	int			t;

	t = -1;
	while (++t < 3 && !(ins->params[t].nb_bytes = 0))
		if ((int)hex &  len[t + 1] << ((3 - t) * 2))
		{
			if ((g_op_tab[ins->op.opcode - 1].arg_types[t] & type[t]))
			{
				ins->params[t].type = type[t];
				ins->params[t].nb_bytes = len[type[t]];
				if (type[t] == DIR_CODE
					&& g_op_tab[ins->op.opcode - 1].describe_address == 1)
					ins->params[t].nb_bytes = 2;
			}
			else
				return (0);
		}
	return (!((hex & 3)) * hex);
}

/*
 ** Check validity of instruction at i, stores in instruction structure
 ** Return 0 if invalid instruction, length of instruction if valid
 ** Input: arena string, int starting point (i), structure to store instruction
 ** details, int size beyond which index circles back
 */

int				get_instruction(char *arena, t_instruction *ins, int i, int mod)
{
	char	hex;
	int	len;

	hex = (char)*(arena + (i >= mod ? 0 : i));
	if (hex >= NB_INSTRUCTIONS || hex < 0)
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&g_op_tab[(int)hex - 1], sizeof(t_op));
	hex = *(arena + ((i + 1) >= mod ? 1 : i + 1));
	if (needs_ocp(hex) && !(ins->ocp = is_valid_ocp(hex, ins)))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	if (!(len = store_arg(arena, ins, i, mod)))
	{
		ft_bzero((void *)ins, sizeof(*ins));
		return (0);
	}
	ins->params->nb_bytes = len -1 - (ins->ocp ? 1 : 0);
	ft_printf("valid instruction >> %s\n", ins->op.description);
	return (len);
}
