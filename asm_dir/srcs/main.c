/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 23:31:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_init_env(t_env *e, char **argv)
{
	e->parser.nb_line = 0;
	e->parser.nb_warnings = 0;
	e->parser.nb_errors = 0;
	e->parser.parsed_name = 0;
	e->parser.parsed_comment = 0;
	e->parser.too_much_errors_displayed = 0;
	e->champ.assembly_name = argv[1];
	e->champ.instructions = NULL;
}

int ft_print_usage(char *progname)
{
	ft_printf("Usage: %s <sourcefile.s>\n", progname);
	return (1);
}

void	ft_show_me_those_amazing_logs(t_env *e)
{
	ft_log_error("ce \"c apostrophe\" possede beaucoup trop de style !",
			"ouai c'est la fete !", 5, e);
	ft_log_warning("en vrai c'est pas si fou que ca c'est qu'un warning..",
			"ouai c'est la fete !", 5, e);
	ft_log_error_no_line("juste une error de plus haha", e);
	ft_log_warning_no_line("juste un warning de plus haha", e);
}

int main(int argc, char **argv)
{
	t_env e;

	if (argc != 2)
		return (ft_print_usage(argv[0]));
	ft_init_env(&e, argv);
//	ft_show_me_those_amazing_logs(&e); //a decommenter de toute urgence
	if (ft_parse_asm(argv[1], &e))
		return (1);
	ft_print_logs_stats(&e);
	return (0);
}
