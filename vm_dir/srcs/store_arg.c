/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:36:33 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 16:53:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		arg_mod(char *arena, t_parameter *arg, int i)
{
	ft_memmove((void *)&arg->value, (void *)(arena + i), IND_SIZE);
	return (IND_SIZE);
}

static int		arg_uni(char *arena, t_parameter *arg, int i)
{
	ft_memmove((void *)&arg->value, (void *)(arena + i), 1);
	return (1);
}

static int			arg_reg(char *arena, t_parameter *arg, int i)
{

	if (arg->nb_bytes & T_REG)
		arg->value = *(char *)(arena + i);
	else if (i + arg->nb_bytes < MEM_SIZE)
		ft_memmove((void *)&arg->value, (void *)(arena + i), arg->nb_bytes);
	else
	{
		ft_memmove((void *)&arg->value, (void *)(arena + i), MEM_SIZE - i);
		ft_memmove((void *)&arg->value, (void *)(arena + i),
				(i + arg->nb_bytes) % MEM_SIZE);
	}
	return (arg->nb_bytes);
}

int		store_arg(char *arena, t_instruction *ins, int i, int ocp)
{
	int	arg;
	int	start;
	static int (*fstore[NB_INSTRUCTIONS])(char *ar, t_parameter *arg, int c) =
	{&arg_mod, &arg_reg, &arg_reg, &arg_reg, &arg_reg, &arg_reg, &arg_reg,
		&arg_reg, &arg_mod, &arg_reg, &arg_reg, &arg_mod, &arg_reg, &arg_reg,
		&arg_mod, &arg_uni};

	arg = -1;
	start = i;
	while (++arg < ins->op.nb_params)
	{
		ft_printf("ocp = %d ins op arg type = %d\n", ocp, ins->op.arg_types[i]);
		ocp = ocp & (11 << i);
		ocp = (ocp >> (i + i));
		if (!(ocp & ins->op.arg_types[i])
				|| ((ocp & T_REG && *(arena + i) >= REG_NUMBER)))
		{
			ft_printf("invalid file type!\n");
			return (0);
		}
		i += fstore[(int)ins->op.opcode](arena, &ins->params[arg], i);
	}
	return (i - start);
}
