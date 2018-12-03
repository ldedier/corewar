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
		return (0);
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (line[i + 1] != '\0')
		return (0);
	printf("name = %s\n", env->champ.header.prog_name);
	return (1);
}

int read_comment(char *line, t_env *env)
{
	int i;
	int j;

	j = 0;
	i = 0;
	i += ft_strlen(COMMENT_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		return (0);
	while (line[i++])
	{
			env->champ.header.comment[j] = line[i];
			if (line[i] == '"')
				break;
			j++;
	}
	env->champ.header.comment[j] = '\0';
	if (line[i + 1] != '\0')
		return (0);
	printf("comment = %s\n", env->champ.header.comment);
  return (1);
}

//devrait mettre a jour
//le parser sur has_comment, has_name

int	ft_parse_line_header(char *str, t_env *env)
{
	int i;

	i = 0;
	if (ft_strstr(str, NAME_CMD_STRING) )
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
			return (0);
		if ((read_name(str, env, i)) == 0)
			return (0);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING) )
	 {
	  i = 0;
	  while (str[i] == ' ' || str[i] == '\t')
	  	i++;
	  if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) != 0)
	  	return (0);
	  if (!(read_comment(str, env)))
	 		return (0);
 	}
	return (1);
}
