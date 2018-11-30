/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:04:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 20:04:53 by ldedier          ###   ########.fr       */
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
		env->champ.name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.name[j] = '\0';
	if (line[i + 1] != '\0')
		return (0);
	printf("%s\n", env->champ.name);
	return (1);
}

/*
int read_comment(t_env env)
{
  return (0);
}
*/

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
		if (!(read_name(str, env, i)))
			return (0);
	}
	/*else if (ft_strstr(str[i], COMMENT_CMD_STRING) )
	  {
	  i = 0;
	  while (str[i] == ' ' || str[i] == '\t')
	  i++;
	  if (ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) != 0)
	  return (0);
	  if (!(check_format_comment(str, env, i)))
	  return (0);
	  }*/
	return (1);
}
