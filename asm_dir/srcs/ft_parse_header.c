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

static int read_name_continue(char *line, int i, t_env *env)
{
	if (line[i] != '"')
	{
		ft_log_error("Lexical error at [1:1]", i - 1, env);
		return (1);
	}
	if (line[i + 1] != '\0')
	{
		while(line[i] || line[i] == ' ' || line[i] == '\t')
		{
			if (ft_isdigit(line[i]) || ft_isalpha(line[i]))
			{
				ft_log_error("Syntax error at token [TOKEN][002] AFTER NAME", i, env);
				return (1);
			}
			i++;
		}
	}
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 128)", env);
	return (0);
}
static int read_name(char *line, t_env *env, int i, int j)
{
	if (env->champ.header.prog_name[j])
	{
		ft_log_error("Syntax error at token COMMAND_NAME", 0, env);
		return (1);
	}
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
	{
		ft_log_error("Lexical error at [1:1]", i, env);
		return (1);
	}
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (read_name_continue(line, i, env) == 1)
		return (1);
	printf("%s\n", env->champ.header.prog_name);
	env->parser.parsed_name = 1;
	return (0);
}

static int check_after_comment(char *tmp, int i, t_env *env)
{
	while(ft_strchr(&tmp[++i], '"'))
		;
	if (tmp[i - 1] != '"')
	{
		printf("ici\n");
		ft_log_error_no_line("Lexical error", env);
		return (1);
	}
	while (tmp[i] || tmp[i] == ' ' || tmp[i] == '\t')
	{
		if (ft_isalpha(tmp[i]) || ft_isdigit(tmp[i]))
		{
			ft_log_error_no_line("Syntax error at token [TOKEN][002] AFTER COMMENT", env);
				return (1);
		}
		i++;
	}
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 128)", env);
	return (0);
}

static int get_comment_other_line(t_env *env, int fd, int i)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(fd, &tmp))
	{
		ft_strcat(env->champ.header.comment, tmp);
		ft_strcat(env->champ.header.comment, "\n");
		if (ft_strchr(tmp, '"'))
			break;
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

static int read_comment_continue(char *line, int i, t_env *env, int fd)
{
	if (line[i] == '\0')
	{
		if (get_comment_other_line(env, fd, 0) == 1)
			return (1);
		i++;
	}
	line++;
	if (line[i + 2] != '\0' && line[i + 1])
	{
		while(line[i] || line[i] == '\t' || line[i] == ' ')
		{
			if (ft_isdigit(line[i]) || ft_isalpha(line[i]))
			{
				ft_log_error("Syntax error at token [TOKEN][002] AFTER COMMENT", i + 1, env);
				return (1);
			}
			i++;
		}
	}
	if (ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 2048)", env);
	printf("comment = %s\n", env->champ.header.comment);
	env->parser.parsed_comment = 1;
	return (0);
}

static int read_comment(char *line, t_env *env, int fd, int i)
{
	int j;

	j = 0;
	if (env->champ.header.comment[j])
	{
		ft_log_error("Syntax error at token COMMAND_COMMENT", 0, env);
		return (1);
	}
	i += ft_strlen(COMMENT_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
	{
		ft_log_error("Lexical error at [2:1]", i, env);
		return (1);
	}
	while(line[i] && line[i + 1] != '"')
		env->champ.header.comment[j++] = line[++i];
	env->champ.header.comment[j] = '\0';
	printf("c = %c\n", line[i]);
	if (env->champ.header.comment[j])
	{
		if (line[i + 1] != '"')
		{
			ft_log_error("Lexical error at [2:13]", i, env);
			return (1);
		}
	}
	if (read_comment_continue(line, i, env, fd) == 1)
		return (1);
	return (0);
}
//devrait mettre a jour
//le parser sur has_comment, has_name

static int check_name(char *str, t_env *env)
{
	char *name;

	name = NULL;
	if (str[0] == '.')
	{
		if (!(name = ft_strndup(str,  ft_strlen(NAME_CMD_STRING))))
			return (1);
		if (ft_strcmp(name, NAME_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error at [1:1]", env));
	}
	else if (str[0] != '.')
	{
		ft_log_error("Lexical error at [1:1]", 0, env);
		return (1);
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
		if (!(comment = ft_strndup(str,  ft_strlen(COMMENT_CMD_STRING))))
			return (1);
		if (ft_strcmp(comment, COMMENT_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error at [2:1]", env));
	}
	else if (str[0] != '.')
	{
		ft_log_error("Lexical error at [2:1]", 0, env);
		return (1);
	}
	free(comment);
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
		if (check_comment(str, env) == 1)
			return (1);
		if (read_comment(str, env, fd, 0) == 1)
			return (1);
	}
	else if (!ft_strcmp(env->champ.header.prog_name, ""))
	{
		ft_log_error_no_line("Lexical error at [1:1]", env);
		return (1);
	}
	else if (!ft_strcmp(env->champ.header.comment, ""))
	{
		ft_log_error_no_line("Lexical error at [1:2]",env);
		return (1);
	}
	return (0);
}
