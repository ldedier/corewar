/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 18:09:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int read_name(char *line, t_env *env, int i)
{
	int j;

	j = 0;
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		return (0);
	if (!(env->champ.name = (char *)malloc(sizeof(char) * 128)))
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


/*int read_comment(t_env env)
  {
  return (0);
  }*/

int parse_line(char **tab, t_env *env, int i)
{
	char *str;

	str = tab[i];
	if (ft_strstr(tab[i], NAME_CMD_STRING) )
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_strncmp(*(tab + i), NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
			return (0);
		if (!(read_name(str, env, i)))
			return (0);
	}
	/*else if (ft_strstr(tab[i], COMMENT_CMD_STRING) )
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


void	ft_print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_printf("instru %d:  %s\n", i,  split[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_env env;

	env.champ.instrus = NULL;
	(void)argc;
	(void)argv;
	ft_bzero(&env, sizeof(t_env));
	if ((read_name_file(argv[1], &env)) == 1)
	{
		ft_printf("Bad syntax source file");
		return (0);
	}
	if ((env.champ.instrus = read_file(argv)))
	{
		ft_print_split(env.champ.instrus);
		printf("instru = %s\n", *env.champ.instrus);
		if (!(parse_line(env.champ.instrus, &env, 0)))
		{
			printf("Bad syntax .name\n");
			return (1);
		}

	}
	return (0);
}
