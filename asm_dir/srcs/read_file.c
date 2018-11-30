/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:57:30 by cammapou          #+#    #+#             */
/*   Updated: 2018/11/30 14:57:33 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char   **read_file(char **argv)
{
  char *str;
  char *line;
  char **split;
	int fd;

  line = NULL;
  str = ft_memalloc(1);
  if ((fd = open(argv[1] , O_RDONLY)) == -1)
  {
    ft_printf("bad file descriptor\n");
    return (0);
  }
  while (get_next_line(fd, &line))
  {
		str = ft_strjoin(str, line);
		str = ft_strjoin(str, "\n\0");
		free(line);
	}
	split = NULL;
	split = ft_strsplit(str, '\n');
	free(str);
  close(fd);
  return (split);
}


int read_name_file(char *argv, t_env *env)
{
	int i;
	char *name;
	int index;

	i = 0;
	if (!argv)
		return (1);
	while (argv[i])
		i++;
	if (argv[i - 1] != 's' || i == 0)
		return (1);
	index = 0;
	if (argv[i - 1] == 's')
	{
		//i = 0;
		name = ft_strndup(&argv[index], i - 2);
		env->champ.file_name = ft_strjoin(name, ".cor");
		printf("name = %s\n", name);
		printf("name = %s\n", env->champ.file_name);
		return (0);
	}
	return (0);
}
