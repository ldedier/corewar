/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:57:30 by cammapou          #+#    #+#             */
/*   Updated: 2018/11/30 18:01:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char   **read_file(char **argv)
{
	char *str;
	char *line;
	char **split;
	int fd;

	str = ft_memalloc(1);
	if ((fd = open(argv[1] , O_RDONLY)) == -1)
	{
		ft_printf("bad file descriptor\n");
		return (0);
	}
	while (get_next_line(fd, &line))
	{
		str = ft_strjoin_free(str, line);
		str = ft_strjoin_free(str, "\n");
		free(line);
	}
	free(line);
	if (!(split = ft_strsplit(str, '\n')))
	{
		free(str);
		close(fd);
		return (0);
	}
	free(str);
	close(fd);
	return (split);
}

int read_name_file(char *str, t_env *env)
{
	int i;
	char *name;
	int index;
	int len;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != '.')
		i++;
	len = i;
	if (str[i + 1] != 's' || i == 0)
		return (1);
	index = i;
	env->champ.file_name = ft_strnew(len + 4);
	if (str[i + 1] == 's')
	{
		i = 0;
		name = ft_strndup(&str[i], index);
		env->champ.file_name = ft_strjoin(name, ".cor");
		printf("name = %s\n", name);
		printf("name = %s\n", env->champ.file_name);
		return (0);
	}
	return (0);
}
