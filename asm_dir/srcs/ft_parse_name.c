/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:21 by cammapou          #+#    #+#             */
/*   Updated: 2019/01/15 19:16:42 by ldedier          ###   ########.fr       */
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
			return (ft_log_error_no_line("Lexical error NAME", env));
	}
	else if (str[0] != '.')
		return (ft_log_error_no_line("Lexical error NAME", env));
	return (0);
}

static int	read_name_continue(char *line, int i, t_env *env)
{
	if (line[i] != '"')
		return (ft_log_error("Lexical error", i - 1, env));
	if (line[i + 1] != '\0')
		while (line[++i] || line[i] == ' ' || line[i] == '\t')
			if (isprint(line[i]))
				return (ft_log_error("Syntax error token AFTER NAME", i - 2, env));
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		return (ft_log_error_no_line("Name too long (Max length 128)", env));
	return (0);
}

int			read_name(char *line, t_env *env, int i, int j)
{
	if (env->champ.header.prog_name[j])
		return (ft_log_error("Syntax error at token COMMAND_NAME", 0, env));
	i = ft_strlen(NAME_CMD_STRING);
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] != '"')
		return (ft_log_error("Lexical error", i, env));
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
//	printf("%s\n", env->champ.header.prog_name);
	env->parser.parsed_name = 1;
	return (0);
}
