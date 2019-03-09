/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:10 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/27 13:06:15 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_after_comment(char *tmp, int i, t_env *env)
{
	while (ft_strchr(&tmp[++i], '"'))
		;
	if (tmp[i - 1] != '"')
		return (ft_log_error_no_line(ERR_LX, env));
	while (tmp[i] || tmp[i] == ' ' || tmp[i] == '\t')
	{
		if (isprint(tmp[i]))
			return (ft_log_error_no_line(ERR_SXC, env));
		i++;
	}
	return (0);
}

static void	check_comment_exist(t_env *env, int j)
{
	if (env->champ.header.comment[j])
	{
		while (env->champ.header.comment[j] != '\0')
			j++;
		env->champ.header.comment[j] = '\n';
	}
}

static void	get_comment_other_line_suite(t_env *env, int i)
{
	while (ft_strchr(&env->champ.header.comment[i], '"'))
		i++;
	if (env->champ.header.comment[i - 1] == '"')
		env->champ.header.comment[i - 1] = '\0';
	env->champ.header.comment[i] = '\0';
}

static int	get_comment_other_line(t_env *env, int fd, int i, int len)
{
	char	*tmp;

	len = ft_strlen(tmp);
	tmp = NULL;
	check_comment_exist(env, 0);
	if (!env->champ.header.comment[i])
		ft_strcat(env->champ.header.comment, "\n");
	while (get_next_line(fd, &tmp))
	{
		if (len + ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
			return (ft_log_error_no_line(ERR_SIZE, env));
		ft_strcat(env->champ.header.comment, tmp);
		ft_strcat(env->champ.header.comment, "\n");
		if (ft_strchr(tmp, '"'))
			break ;
		free(tmp);
	}
	if (check_after_comment(tmp, i, env) == 1)
		return (1);
	get_comment_other_line_suite(env, i);
	free(tmp);
	return (0);
}

int	read_comment_continue(char *line, int i, t_env *env, int fd)
{
	if (line[i] == '\0')
	{
		if (get_comment_other_line(env, fd, 0, 0) == 1)
			return (1);
		i++;
	}
	i += 1;
	if (line[i] == '"')
	{
		i += 1;
		while (line[i] || line[i] == '\t' || line[i] == ' ')
		{
			if (isprint(line[i]))
				return (ft_log_error(ERR_SXC, i, env));
			i++;
		}
	}
	if (ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
		ft_log_error_no_line(ERR_SIZE, env);
	env->parser.parsed_comment = 1;
	return (0);
}
