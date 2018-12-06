/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:13:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 12:16:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_process_parse_chunk(t_chunk chunk, t_env *e)
{
	(void)chunk;
	(void)e;


	return (0);
}

int		ft_process_parse_cor(int fd, t_env *e)
{
	t_chunk	chunk;

	while (get_next_chunk(fd, &chunk))
	{
		if (ft_process_parse_chunk(chunk, e))
			return (1);
	}
	return (0);
}

int		ft_parse_cor(char *filename, t_env *e)
{
	int fd;
	int ret;

	if ((fd = open(filename , O_RDONLY)) == -1)
	{
		perror(filename);
		return (1);
	}
	else if (((ret = ft_switch_extension(filename, ".cor", "_decomp.s",
		&(e->champ.assembly_name)))))
	{
		if (ret == -1)
			ft_printf("malloc error\n");
		else
			ft_printf("file must be of extension \'.cor\'\n");
		return (1);
	}
	return (ft_process_parse_cor(fd, e));
}
