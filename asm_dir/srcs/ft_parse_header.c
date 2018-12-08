/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:04:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/04 11:38:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// j'ai change les char * en char[PROG_NAME] etc (voir struct s_champion)

static int read_name(char *line, t_env *env, int i, int j)
{
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		ft_log_error("Syntax error at token [TOKEN][001] NAME", 5, env);
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (line[i] != '\0' && line[i + 1])
		while(line[i] || line[i] == '\t' || line[i] == ' ')
		{
			if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
			{
				ft_log_error_no_line("Syntax error at token [TOKEN][002] AFTER NAME", env);
				return (1);
			}
			i++;
		}
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 128)", env);
	printf("name = %s\n", env->champ.header.prog_name);
	return (0);
}

static int get_comment_other_line(t_env *env, int fd)
{
	char	*tmp;
	int i;

	tmp = NULL;
	i = 0;
	while (get_next_line(fd, &tmp))
	{
		ft_strcat(env->champ.header.comment, tmp);
		ft_strcat(env->champ.header.comment, "\n");
		if (ft_strchr(tmp, '"'))
			break;
		free(tmp);
	}
	while(ft_strchr(&tmp[++i], '"'))
		;
	while (tmp[i])
	{
		if (ft_isalpha(tmp[i]) || ft_isdigit(tmp[i]))
			return (1);
		i++;
	}
	while (ft_strchr(&env->champ.header.comment[i], '"'))
		i++;
	if (env->champ.header.comment[i - 1] == '"')
		env->champ.header.comment[i - 1] = '\0';
	free(tmp);
	return (0);
}

int after_comment(char *line, int i, t_env *env)
{
	if (line[i] != '\0' && line[i + 1])
		while(line[i] || line[i] == '\t' || line[i] == ' ')
		{
			if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
			{
				ft_log_error_no_line("Syntax error at token [TOKEN][002] AFTER COMMENT", env);
				return (1);
			}
			i++;
		}
	return (0);
}

static int read_comment(char *line, t_env *env, int fd, int i)
{
	int j;

	j = 0;
	while (*line && *line != COMMENT_CHAR && *line != '"')
		line++;
	if (line[i] != '"' || line[i] == '\0')
		ft_log_error_no_line("Syntax error at token [TOKEN][002]", env);
	line++;
	while(line[i] && line[i] != '"')
		env->champ.header.comment[j++] = line[i++];
	env->champ.header.comment[j] = '\0';
	if (line[i] == '\0')
		if (get_comment_other_line(env, fd) == 1)
			ft_log_error_no_line("Syntax error at token [TOKEN][002] COMMENT", env);
	after_comment(line, i, env);
	if (ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 2048)", env);
	printf("comment = %s\n", env->champ.header.comment);
	return (0);
}
//devrait mettre a jour
//le parser sur has_comment, has_name

static int check_name(char *str, t_env *env)
{
	int i;
	char *name;

	i = 0;
	name = NULL;

	if (str[0] == '.')
	{
		name = ft_strndup(str,  ft_strlen(NAME_CMD_STRING));
		if (ft_strcmp(name, NAME_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error at [1:1]", env));
	}
	free(name);
	return (0);
}

static int check_comment(char *str, t_env *env)
{
	int i;
	char *comment;

	i = 0;
	comment = NULL;
	if (str[0] == '.')
	{
		comment = ft_strndup(str,  ft_strlen(COMMENT_CMD_STRING));
		if (ft_strcmp(comment, COMMENT_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error at [2:1]", env));
	}
	free(comment);
	return (0);
}

int verif_format(char *str, t_env *env)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))\
	 	!= 0)
		return (ft_log_error_no_line("Syntax error at token [TOKEN][002] INSTRUCTION", env));
	i += ft_strlen(COMMENT_CMD_STRING);
	while (str[i] && str[i] != '"')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (ft_log_error("Syntax error at token [TOKEN][002] COMMENT", 8,env));
		i++;
	}
	return (0);
}

int check_format(char *str, t_env *env)
{
	int i;

	i = 0;
	if (str[i + 1] == 'n' && str[i] == '.')
		if (check_name(str, env) == 1)
			return (1);
	if (str[i + 1] == 'c' && str[i] == '.')
		if (check_comment(str, env) == 1)
			return (1);
	return (0);
}

int	ft_parse_line_header(char *str, t_env *env, int i, int fd)
{
	if (check_format(str, env) == 1)
		return (1);
	if (ft_strstr(str, NAME_CMD_STRING) )
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
			return (ft_log_error_no_line("Syntax error at token [001] NAME", env));
		if (read_name(str, env, i, 0) == 1)
			return (1);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))\
				!= 0)
			return (ft_log_error_no_line("Syntax error at token [002] COMMENT", env));
		if (verif_format(str, env) == 1)
			return (1);
		if (read_comment(str, env, fd, 0) == 1)
			return (1);
	}
	return (0);
}
