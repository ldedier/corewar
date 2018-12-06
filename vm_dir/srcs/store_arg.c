/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:36:33 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 21:41:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			memmove_arg(char *arena, t_parameter *arg, int i, int mod)
{
	if (i + arg->nb_bytes < mod)
		ft_memmove((void *)&arg->value, (void *)(arena + i), arg->nb_bytes);
	else
	{
		ft_memmove((void *)&arg->value, (void *)(arena + i), MEM_SIZE - i);
		ft_memmove((void *)&arg->value, (void *)(arena + i),
				(i + arg->nb_bytes) % mod);
	}
	if (arg->type == REG_CODE && (arg->value >= REG_SIZE || arg->value < 0))
		return (0);
	return (arg->nb_bytes);
}

// mettre un argument de taille
int		store_arg(char *arena, t_instruction *ins, int i, int mod)
{
	int	arg;
	int	start;

	arg = -1;
	start = i;
	while (++arg < ins->op.nb_params)
		if (!(i += memmove_arg(arena, &ins->params[arg], i, mod)))
			return (0);
	return (i - start);
}
