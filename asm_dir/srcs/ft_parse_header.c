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

static int error(int error)
{
	if (error == 1)
	{
		ft_printf("Syntax error at token [TOKEN][001]\n");
		return (0);
	}
	if (error == 2)
	{
		ft_printf("Syntax error at token [TOKEN][002]\n");
		return (0);
	}
	if (error == 3)
	{
		ft_printf("Lexical error\n");
		return (0);
	}
	if (error == 4)
	{
		printf("Champion name too long (Max length 128)\n");
		return (0);
	}
	if (error == 5)
	{
		printf("Champion comment too long (Max length 2048)\n");
		return (0);
	}
	return (1);
}

static int read_name(char *line, t_env *env, int i)
{
	int j;

	j = 0;
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		if (error(1) == 0)
			return (0);
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		if (error(4) == 0)
			return (0);
	printf("name = %s\n", env->champ.header.prog_name);
	return (1);
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
	if (line[i] != '"')
		if (error(1) == 0)
			return (0);
	while (line[i++])
	{
		env->champ.header.comment[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.comment[j] = '\0';
	if (ft_strlen(env->champ.header.comment) > COMMENT_LENGTH)
		if (error(5) == 0)
			return (0);
	printf("comment = %s\n", env->champ.header.comment);
	return (1);
}

//devrait mettre a jour
//le parser sur has_comment, has_name

static int check_name(char *str)
{
	int i;
	char *name;

	i = 0;
	name = NULL;
	if (str[0] == '.')
	{
		name = ft_strndup(str,  ft_strlen(NAME_CMD_STRING));
		if (ft_strcmp(name, NAME_CMD_STRING) != 0)
			if (error(3) == 0)
				return (0);
	}
	free(name);
	return (1);
}

static int check_comment(char *str)
{
	int i;
	char *comment;

	i = 0;
	comment = NULL;
	if (str[0] == '.')
	{
		comment = ft_strndup(str,  ft_strlen(COMMENT_CMD_STRING));
		if (ft_strcmp(comment, COMMENT_CMD_STRING) != 0)
			if (error(3) == 0)
				return (0);
	}
	free(comment);
	return (1);
}

int	ft_parse_line_header(char *str, t_env *env, int i)
{
	if (ft_strstr(str, NAME_CMD_STRING) )
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
			if (error(1) == 0)
				return (0);
		if ((read_name(str, env, i)) == 0)
			return (0);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) != 0)
			if (error(2) == 0)
				return (0);
		if (!(read_comment(str, env)))
			return (0);
	}
	if (str[i + 1] == 'n')
		if (check_name(str) == 0)
			return (0);
	if (str[i + 1] == 'c')
		if (check_comment(str) == 0)
			return (0);
	return (1);
}
