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

int			read_comment(char *line, t_env *env, int fd, int i)
{
	int		j;

	j = 0;
	if (env->champ.header.comment[j])
		return (ft_log_error("Syntax error", 0, env));
	i = ft_strlen(COMMENT_CMD_STRING);
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] != '"')
		return (ft_log_error(ERR_LX, i, env));
	while (line[i] && line[i + 1] != '"')
		env->champ.header.comment[j++] = line[++i];
	env->champ.header.comment[j] = '\0';
	if (line[i + 1] != '"' && line[i] != '\0')
		return (ft_log_error(ERR_LX, i, env));
	if (read_comment_continue(line, i, env, fd) == 1)
		return (1);
	return (0);
}

int	ft_parse_line_header(char *str, t_env *env, int i, int fd)
{
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		if (check_name(str, env) == 1)
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
		return (ft_log_error_no_line(ERR_LXN, env));
	else if (!ft_strcmp(env->champ.header.comment, ""))
		return (ft_log_error_no_line(ERR_LXC, env));
	return (0);
}
