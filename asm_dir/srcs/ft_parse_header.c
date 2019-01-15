/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:40:58 by cammapou          #+#    #+#             */
/*   Updated: 2018/12/19 13:41:03 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	isprint(int c)
{
	if ((c >= 33 && c <= 62) || (c >= 64 && c <= 126))
		return (1);
	return (0);
}

int	ft_parse_line_header(char *str, t_env *env, int i, int fd)
{
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		if (check_name(str, env))
			return (1);
		if (read_name(str, env, i, 0) == 1)
			return (1);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		if (check_comment(str, env))
			return (1);
		if (read_comment(str, env, fd, 0) == 1)
			return (1);
	}
	else if (!ft_strcmp(env->champ.header.prog_name, ""))
		return (ft_log_error_no_line("Lexical error NAME", env));
	else if (!ft_strcmp(env->champ.header.comment, ""))
		return (ft_log_error_no_line("Lexical error COMMENT", env));
	return (0);
}
