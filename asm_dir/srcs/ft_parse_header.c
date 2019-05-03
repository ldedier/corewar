/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 04:38:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/15 01:14:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	end_parse(t_env *e)
{
	if (e->parser.parsing_name)
	{
		e->parser.parsing_name = 0;
		e->parser.parsed_name = 1;
	}
	else
	{
		e->parser.parsing_comment = 0;
		e->parser.parsed_comment = 1;
	}
}

int		is_comment(char c)
{
	return (c == ';' || c == COMMENT_CHAR);
}

int		ft_parse_comment(char *str, int i, t_env *e)
{
	if (e->parser.parsed_comment)
		return (ft_log_error("comment already parsed", 0, e));
	i += sizeof(COMMENT_CMD_STRING) - 1;
	e->parser.column_offset += sizeof(COMMENT_CMD_STRING) - 1;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i] != '"')
		return (ft_log_error("expected\'\"\' character", 0, e));
	else
		return (ft_process_parse_comment(&str[++i], e));
}

int		ft_parse_name(char *str, int i, t_env *e)
{
	if (e->parser.parsed_name)
		return (ft_log_error("name already parsed", 0, e));
	i += sizeof(NAME_CMD_STRING) - 1;
	e->parser.column_offset += sizeof(NAME_CMD_STRING) - 1;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i] != '"')
		return (ft_log_error("expected\'\"\' character", 0, e));
	else
		return (ft_process_parse_name(&str[++i], e));
}

int		ft_parse_line_header(char *str, t_env *e)
{
	int i;

	if (e->parser.parsing_comment)
		return (process_fill_buffer(str, COMMENT_LENGTH,
					e->champ.header.comment, e));
	else if (e->parser.parsing_name)
		return (process_fill_buffer(str, PROG_NAME_LENGTH,
					e->champ.header.prog_name, e));
	else
	{
		i = 0;
		while (ft_isseparator(str[i]) && ft_addco(str[i], e))
			i++;
		if (is_comment(str[i]))
			return (0);
		else if (ft_strstr(&str[i], COMMENT_CMD_STRING) == &(str[i]))
			return (ft_parse_comment(str, i, e));
		else if (ft_strstr(&str[i], NAME_CMD_STRING) == &(str[i]))
			return (ft_parse_name(str, i, e));
		else
			return (ft_log_error("unknown command", 0, e));
	}
	return (0);
}
