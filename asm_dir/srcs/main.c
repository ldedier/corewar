/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/14 20:30:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_print_usage(char *progname)
{
	ft_printf("Usage: %s <sourcefile.s>\n", progname);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	e;
	int		ret;

	ret = 0;
	if (argc < 2)
		return (ft_print_usage(argv[0]));
	ft_init_env(&e, argv[argc - 1]);
	if (ft_parse_asm(argv[argc - 1], &e))
	{
		ft_print_logs_stats(&e);
		ft_free_all(&e);
		return (1);
	}
	ft_print_logs_stats(&e);
	if (ft_encode_to_cor(e.champ.cor_name, &e))
		ret = 1;
	else
		ft_printf("successfully compiled %s at %s\n", e.champ.assembly_name,
				e.champ.cor_name);
	ft_free_all(&e);
	return (ret);
}
