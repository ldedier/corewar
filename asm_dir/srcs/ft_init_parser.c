/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:07:52 by cammapou          #+#    #+#             */
/*   Updated: 2019/01/15 17:08:55 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_init_parser(t_parser *parser)
{
	parser->nb_line = 0;
	parser->column_offset = 0;
	parser->nb_warnings = 0;
	parser->nb_errors = 0;
	parser->parsed_name = 0;
	parser->parsed_comment = 0;
	parser->too_much_errors_displayed = 0;
}

void		ft_reset_parser(t_parser *parser, char *str)
{
	parser->nb_args_parsed = 0;
	parser->current_line = str;
	parser->column_offset = 0;
}

int			ft_set_parser_co(int save, t_env *e, int ret)
{
	(void)save;
	(void)e;
	return (ret);
}
