/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:47:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 17:12:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int	ft_print_usage(char *progname)
{
	ft_printf("Usage: %s [-l] <sourcefile.cor>\n", progname);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	e;
	int		ret;

	ret = 0;
	if (argc != 2 && argc != 3)
		return (ft_print_usage(argv[0]));
	if (ft_init_env(&e, argc, argv))
	{
		ft_free_all(&e);
		return (1);
	}
	if (ft_read_player(e.champ.cor_name, &(e.player)))
	{
		ft_free_all(&e);
		return (1);
	}
	if (ft_encode_to_assembly(&e))
		ret = 1;
	ft_free_all(&e);
	return (ret);
}
