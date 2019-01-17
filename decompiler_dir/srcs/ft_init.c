/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:50:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 01:26:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_init_env(t_env *e, int argc, char **argv)
{
	int ret;

	e->champ.cor_name = argv[argc - 1];
	e->create_labels = 0;
	if (argc == 3)
	{
		if (!ft_strcmp("-l", argv[1]))
			e->create_labels = 1;
		else
		{
			ft_dprintf(2, "%s: invalid option\n", argv[1]);
			return (1);
		}
	}
	if ((ret = ft_switch_extension(e->champ.cor_name, ".cor", "_decomp.s",
					&(e->champ.assembly_name))))
	{
		if (ret == -1)
			return (ft_return_verbosed("malloc error", 1));
		else
			return (ft_return_verbosed(
						"file must be of exension \'.cor\'", 1));
	}
	return (0);
}
