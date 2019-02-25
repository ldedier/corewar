/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:21 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/25 16:13:01 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_name(char *str, t_env *env)
{
	int i;

	if (str[0] == '.')
	{
		i = ft_strlen(NAME_CMD_STRING);
		if (isprint(str[i]) == 1)
			return (ft_log_error_no_line(ERR_LXN, env));
	}
	else if (str[0] != '.')
		return (ft_log_error_no_line(ERR_LXN, env));
	return (0);
}

static int	read_name_continue(char *line, int i, t_env *env)
{
	if (line[i] != '"')
		return (ft_log_error(ERR_LX, i - 1, env));
	if (line[i + 1] != '\0')
		while (line[++i] || line[i] == ' ' || line[i] == '\t')
			if (isprint(line[i]))
				return (ft_log_error(ERR_SXN, i - 2, env));
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		return (ft_log_error_no_line(ERR_SIZEN, env));
	return (0);
}

int			read_name(char *line, t_env *env, int i, int j)
{
	if (env->champ.header.prog_name[j])
		return (ft_log_error("Syntax error", 0, env));
	i = ft_strlen(NAME_CMD_STRING);
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] != '"')
		return (ft_log_error(ERR_LX, i, env));
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break ;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (read_name_continue(line, i, env) == 1)
		return (1);
	env->parser.parsed_name = 1;
	return (0);
}
