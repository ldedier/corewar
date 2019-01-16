/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/16 18:06:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void __attribute__((destructor)) end();

void    end(void) //permet de mieux checker les leaks !
{
//	ft_printf("destructor loop\n");
//	while(1);
}

int ft_print_usage(char *progname)
{
	ft_printf("Usage: %s <sourcefile.s>\n", progname);
	return (1);
}

void	ft_show_me_those_amazing_logs(t_env *e)
{
	e->parser.current_line = ft_strdup("ouai c'est la fete !");
	ft_log_error("ce \"c apostrophe\" possede beaucoup trop de style !", 5, e);
	e->parser.column_offset = 3;
	ft_log_warning("en fait c juste un warning", 2, e);
	ft_log_error_no_line("juste une error de plus haha", e);
	ft_log_warning_no_line("juste un warning de plus haha", e);
}

int main(int argc, char **argv)
{
	t_env	e;
	int		ret;

	ret = 0;
	if (argc < 2)
		return (ft_print_usage(argv[0]));
	ft_init_env(&e, argv[argc - 1]);
//		ft_show_me_those_amazing_logs(&e); //a decommenter de toute urgence
	if (ft_parse_asm(argv[argc - 1], &e))
	{
		ft_free_all(&e);
		return (1);
	}
	if (ft_encode_to_cor(e.champ.cor_name, &e))
		ret = 1;
	ft_free_all(&e);
	return (ret);
}
