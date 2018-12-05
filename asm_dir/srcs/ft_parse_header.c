/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:04:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/01 15:34:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// j'ai change les char * en char[PROG_NAME] etc (voir struct s_champion)

static int read_name(char *line, t_env *env, int i)
{
	int j;

	j = 0;
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		ft_log_error_no_line("Syntax error at token [TOKEN][001:006] INSTRUCTION", env);
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		ft_log_error_no_line("Champion name too long (Max length 128)", env);
	printf("name = %s\n", env->champ.header.prog_name);
	return (0);
}

static int read_comment(char *line, t_env *env)
{
	int i;
	int j;

	j = 0;
	i = 0;
	i += ft_strlen(COMMENT_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n')
		i++;
	printf("str = %s\n", line);
	printf("str[i] = %c\n", line[i]);
	if (line[i] != '"')
		ft_log_error_no_line("Syntax error at token [TOKEN][002] INSTRUCTION", env);
	while (line[i++])
	{
		env->champ.header.comment[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.comment[j] = '\0';
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

int	ft_parse_line_header(char *str, t_env *env, int i)
{
	if (ft_strstr(str, NAME_CMD_STRING) )
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
			return (ft_log_error_no_line("Syntax error at token [TOKEN][001] INSTRUCTION", env));
		if (read_name(str, env, i) == 1)
			return (1);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) != 0)
			return (ft_log_error_no_line("Syntax error at token [TOKEN][002] INSTRUCTION", env));
		if (read_comment(str, env) == 1)
			return (1);
	}
	if (str[i + 1] == 'n' && str[i] == '.')
		if (check_name(str, env) == 1)
			return (1);
	if (str[i + 1] == 'c' && str[i] == '.')
		if (check_comment(str, env) == 1)
			return (1);
	return (0);
}
