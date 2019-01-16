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

void		ft_reset_parser(t_parser *parser, char *str)
{
	parser->nb_args_parsed = 0;
	parser->current_line = str;
	parser->column_offset = 0;
}

void		ft_init_parameter(t_parameter *parameter)
{
	parameter->type = 0;
	parameter->value = 0;
	parameter->source_code_col = 0;
	parameter->label_name = NULL;
}

int			ft_init_instruction(t_instruction *instruction, t_env *e)
{
	int		i;

	instruction->address = e->champ.header.prog_size;
	instruction->nb_line = e->parser.nb_line;
	instruction->ocp = 0;
	i = 0;
	while (i < 3)
	{
		ft_init_parameter(&(instruction->params[i]));
		i++;
	}
	if (!(instruction->source_code_line = ft_strdup(e->parser.current_line)))
		return (1);
	return (0);
}

int			ft_set_parser_co(int save, t_env *e, int ret)
{
	(void)save;
	(void)e;
//	save = e->parser.column_offset;
	return (ret);
}
