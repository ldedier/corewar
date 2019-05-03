/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 22:00:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/09 20:40:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_log_warning(char *str, int column, t_env *e)
{
	int	col_true;

	col_true = column + e->parser.column_offset;
	ft_printf("%s%s%s:%d:%d: %swarning: %s%s%s\n", BOLD, WHITE,
			e->champ.assembly_name, e->parser.nb_line,
				col_true, MAGENTA, WHITE, str, EOC);
	ft_printf("%s\n", e->parser.current_line);
	ft_printf("%s%*c%s\n", L_GREEN, col_true + 1, '^', EOC);
	e->parser.nb_warnings++;
	return (1);
}

int		ft_log_warning_no_line(char *str, t_env *e)
{
	ft_printf("%s%s%s: %swarning: %s%s%s\n", BOLD, WHITE,
			e->champ.assembly_name, MAGENTA, WHITE, str, EOC);
	e->parser.nb_warnings++;
	return (1);
}

void	ft_print_logs_stats(t_env *e)
{
	if (e->parser.nb_errors && e->parser.nb_warnings)
		ft_printf("%d warning%s and %d error%s generated\n",
			e->parser.nb_warnings, e->parser.nb_warnings > 1 ? "s" : "",
				e->parser.nb_errors, e->parser.nb_errors > 1 ? "s" : "");
	else if (e->parser.nb_errors)
		ft_printf("%d error%s generated\n",
				e->parser.nb_errors, e->parser.nb_errors > 1 ? "s" : "");
	else if (e->parser.nb_warnings)
		ft_printf("%d warning%s generated\n",
				e->parser.nb_warnings, e->parser.nb_warnings > 1 ? "s" : "");
}
