/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:06:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/14 22:28:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_parse_line(char *str, t_env *e)
{
	char	*refined;
	int		ret;

	if (!(refined = ft_refine_line(str, e)))
		return (ft_log_error_no_line(MALLOC_ERROR, e));
	if (!e->parser.parsed_comment || !e->parser.parsed_name)
	{
		ft_reset_parser(&(e->parser), str);
		ret = ft_parse_line_header(refined, e);
		free(refined);
	}
	else
	{
		ret = ft_parse_line_source_code(refined, e);
		free(refined);
	}
	return (ret);
}

static int	ft_process_parse_asm_2(t_env *e)
{
	if (!e->parser.parsed_name)
		return (ft_log_error_no_line("no name found", e));
	else if (!e->parser.parsed_comment)
		return (ft_log_error_no_line("no comment found", e));
	else
		return (ft_fill_instructions_labels_values(e));
}

static int	ft_log_separator_error(t_env *e, int separator)
{
	if (separator == E_SEPARATOR_EOF)
		return (ft_log_error_no_line(EOF_SEPARATOR, e));
	else
		return (ft_log_error_no_line(ZERO_SEPARATOR, e));
}

static int	ft_process_parse_asm(t_env *e)
{
	int			gnl_ret;
	t_gnl_info	info;

	while ((gnl_ret = get_next_line2(e->parser.fd, &info)) == 1)
	{
		e->parser.nb_line++;
		if (info.separator != E_SEPARATOR_NL)
		{
			free(info.line);
			return (ft_log_separator_error(e, info.separator));
		}
		if (ft_is_relevant(info.line, e))
		{
			if (ft_parse_line(info.line, e) == 1)
				return (ft_free_turn(info.line, 1));
		}
		free(info.line);
	}
	close(e->parser.fd);
	if (gnl_ret == -1)
		return (1);
	free(info.line);
	return (ft_process_parse_asm_2(e));
}

int			ft_parse_asm(char *str, t_env *e)
{
	int		ret;

	if ((e->parser.fd = open(str, O_RDONLY)) == -1)
	{
		perror(str);
		return (1);
	}
	else if ((ret = ft_switch_extension(str, ".s", ".cor",
					&(e->champ.cor_name))))
	{
		if (ret == -1)
			return (ft_log_error_no_line(MALLOC_ERROR, e));
		else
			return (ft_log_error_no_line("File must be of extension \'.s\'",
						e));
	}
	if (ft_process_parse_asm(e) == 1)
		return (1);
	return (0);
}
