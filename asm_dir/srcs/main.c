/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 16:16:26 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**void __attribute__((destructor)) end();
**
**void    end(void) //permet de mieux checker les leaks !
**{
**	ft_printf("destructor loop\n");
**	while(1);
**}
*/

int		ft_print_usage(char *progname)
{
	ft_printf("Usage: %s <sourcefile.s>\n", progname);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	e;
	int		ret;

	ret = 0;
	if (argc < 2)
		return (ft_print_usage(argv[0]));
	ft_init_env(&e, argv[argc - 1]);
	if (ft_parse_asm(argv[argc - 1], &e))
	{
		ft_free_all(&e);
		return (1);
	}
	if (ft_encode_to_cor(e.champ.cor_name, &e))
		ret = 1;
	else
		ft_printf("successfully compiled %s at %s\n", e.champ.assembly_name,
				e.champ.cor_name);
	ft_free_all(&e);
	return (ret);
}
