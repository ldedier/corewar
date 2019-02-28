/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:03:52 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/27 13:03:56 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_comment(char *str, t_env *env)
{
	int	i;

	if (str[0] == '.')
	{
		i = ft_strlen(COMMENT_CMD_STRING);
		if (isprint(str[i]) == 1)
			return (ft_log_error_no_line(ERR_LXC, env));
	}
	else if (str[0] != '.')
		return (ft_log_error_no_line(ERR_LXC, env));
	return (0);
}

int		ft_process_nb_params_coherent(int *save, t_env *e, char c)
{
	if (!e->parser.parse_param && !ft_isseparator(c) && c != SEPARATOR_CHAR)
		e->parser.parse_param = 1;
	if (c == SEPARATOR_CHAR)
	{
		if (!e->parser.parse_param)
		{
			if (*save != -1)
				e->parser.column_offset = *save;
			else
				e->parser.column_offset--;
			ft_log_error("empty argument", 0, e);
			return (1);
		}
		*save = e->parser.column_offset;
		e->parser.parse_param = 0;
		e->parser.nb_params += 1;
		if (e->parser.nb_params > e->parser.current_instruction->op->nb_params)
		{
			ft_log_custom_nb_params_error(e);
			return (1);
		}
	}
	return (0);
}

int		ft_process_parse_param(char *param, int index, t_env *e)
{
	if (param[0] == REGISTER_CHAR)
		return (ft_process_parse_register(&(param[1]), index, e));
	else if (ft_isdigit(param[0]) || param[0] == '-' || param[0] == LABEL_CHAR)
		return (ft_process_parse_indirect(param, index, e));
	else if (param[0] == DIRECT_CHAR)
		return (ft_process_parse_direct(&(param[1]), index, e));
	else
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}
