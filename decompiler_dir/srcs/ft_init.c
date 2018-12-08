/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:50:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 16:17:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_init_env(t_env *e, char *filename)
{
	int ret;

	e->champ.cor_name = filename;
	if ((ret = ft_switch_extension(filename, ".cor", "_decomp.s",
		&(e->champ.assembly_name))))
	{
		if (ret == -1)
			return (ft_return_verbosed("malloc error", 1));
		else
			return (ft_return_verbosed(
				"file must be of exension \'.cor\'",
					1));
	}
	return (0);
}
