/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:10 by cammapou          #+#    #+#             */
/*   Updated: 2018/12/19 13:48:11 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_comment(char *str, t_env *env)
{
	char *comment;

	comment = NULL;
	if (str[0] == '.')
	{
		if (!(comment = ft_strndup(str, ft_strlen(COMMENT_CMD_STRING))))
			return (1);
		if (ft_strcmp(comment, COMMENT_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error COMMENT", env));
	}
	else if (str[0] != '.')
		return (ft_log_error("Lexical error BEFORE COMMENT", 0, env));
	free(comment);
	return (0);
}

static int	check_after_comment(char *tmp, int i, t_env *env)
{
	while (ft_strchr(&tmp[++i], '"'))
		;
	if (tmp[i - 1] != '"')
		return (ft_log_error_no_line("Lexical error", env));
	while (tmp[i] || tmp[i] == ' ' || tmp[i] == '\t')
	{
		if (isprint(tmp[i]))
			return (ft_log_error_no_line("Syntax error AFTER COMMENT", env));
		i++;
	}
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 128)", env);
	return (0);
}

static int	get_comment_other_line(t_env *env, int fd, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	if (env->champ.header.comment[j])
	{
		while (env->champ.header.comment[j] != '\0')
			j++;
		env->champ.header.comment[j] = '\n';
	}
	while (get_next_line(fd, &tmp))
	{
		if (ft_strlen(tmp) + ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
			return (ft_log_error_no_line("Syntax error COMMENT", env));
		ft_strcat(env->champ.header.comment, tmp);
		ft_strcat(env->champ.header.comment, "\n");
		if (ft_strchr(tmp, '"'))
			break ;
		free(tmp);
	}
	if (check_after_comment(tmp, i, env) == 1)
		return (1);
	while (ft_strchr(&env->champ.header.comment[i], '"'))
		i++;
	if (env->champ.header.comment[i - 1] == '"')
		env->champ.header.comment[i - 1] = '\0';
	free(tmp);
	return (0);
}

static int	read_comment_continue(char *line, int i, t_env *env, int fd)
{
	if (line[i] == '\0')
	{
		if (get_comment_other_line(env, fd, 0, 0) == 1)
			return (1);
		i++;
	}
	line++;
	i += 1;
	while (line[i] || line[i] == '\t' || line[i] == ' ')
	{
		if (isprint(line[i]))
			return (ft_log_error("Syntax error AFTER COMMENT", i + 1, env));
		i++;
	}
	if (ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 2048)", env);
	printf("%s\n", env->champ.header.comment);
	env->parser.parsed_comment = 1;
	return (0);
}

int			read_comment(char *line, t_env *env, int fd, int i)
{
	int j;

	j = 0;
	if (env->champ.header.comment[j])
		return (ft_log_error("Syntax error COMMAND_COMMENT", 0, env));
	i += ft_strlen(COMMENT_CMD_STRING);
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] != '"')
		return (ft_log_error("Lexical error", i - 1, env));
	while (line[i] && line[i + 1] != '"')
		env->champ.header.comment[j++] = line[++i];
	env->champ.header.comment[j] = '\0';
	if (line[i + 1] != '"' && line[i] != '\0')
		return (ft_log_error("Lexical error", i, env));
	if (read_comment_continue(line, i, env, fd) == 1)
		return (1);
	return (0);
}
