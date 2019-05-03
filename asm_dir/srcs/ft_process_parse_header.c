/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_parse_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 21:59:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/15 01:42:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** buffer len doesn't count the terminating \0
*/

int		process_fill_buffer(char *str, int buffer_len, char *buffer, t_env *e)
{
	int i;
	int tmp;

	tmp = e->parser.parsed_chars;
	i = 0;
	while (str[i] && str[i] != '"' &&
			e->parser.parsed_chars < buffer_len && ft_addco(str[i], e))
		buffer[e->parser.parsed_chars++] = str[i++];
	if (str[i] == '"')
	{
		i++;
		e->parser.column_offset++;
		end_parse(e);
		while (ft_isseparator(str[i]) && ft_addco(str[i], e))
			i++;
		if (str[i] && !is_comment(str[i]))
			return (ft_log_error(LEXICAL_ERROR, 0, e));
		return (0);
	}
	else if (e->parser.parsed_chars == buffer_len)
		return (ft_log_error_too_long_parsing(0, e));
	else
		buffer[e->parser.parsed_chars++] = '\n';
	return (0);
}

int		ft_process_parse_comment(char *str, t_env *e)
{
	int i;

	e->parser.column_offset++;
	i = 0;
	e->parser.parsing_comment = 1;
	e->parser.parsed_chars = 0;
	return (process_fill_buffer(str, COMMENT_LENGTH,
				e->champ.header.comment, e));
}

int		ft_process_parse_name(char *str, t_env *e)
{
	int i;

	e->parser.column_offset++;
	i = 0;
	e->parser.parsing_name = 1;
	e->parser.parsed_chars = 0;
	return (process_fill_buffer(str, PROG_NAME_LENGTH,
				e->champ.header.prog_name, e));
}
