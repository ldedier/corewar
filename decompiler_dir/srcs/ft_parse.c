/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:13:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 18:00:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_is_of_extension(char *str, int length, char *extension,
			int ext_length)
{
	int i;
	int j;

	if (length < ext_length)
		return (0);
	i = length - ext_length;
	j = 0;
	while (i < length)
	{
		if (str[i] != extension[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

int read_name_file(char *str, char *ext_from, char *ext_to, char **new_name)
{
	char *name;
	int len;
	int len_ext_to;
	int len_ext_from;

	len = ft_strlen(str);
	len_ext_to = ft_strlen(ext_to);
	len_ext_from = ft_strlen(ext_from);
	if (ft_is_of_extension(str, len, ext_from, len_ext_from))
	{
		if ((!(name = ft_strndup(str, len - len_ext_from))))
			return (-1);
		if (!(*new_name = ft_strjoin_free(name, ext_to)))
			return (-1);
		ft_printf("%s\n", *new_name);
		return (0);
	}
	else
		return (1);
}

int		ft_process_parse_chunk(t_chunk chunk, t_env *e)
{
	(void)chunk;
	(void)e;


	return (0);
}

int		ft_process_parse_cor(int fd, t_env *e)
{
	t_chunk	chunk;

	while (get_next_chunk(fd, &chunk))
	{
		if (ft_process_parse_chunk(chunk, e))
			return (1);
	}
	return (0);
}

int		ft_parse_cor(char *filename, t_env *e)
{
	int fd;
	int ret;

	if ((fd = open(filename , O_RDONLY)) == -1)
	{
		perror(filename);
		return (1);
	}
	else if (((ret = read_name_file(filename, ".cor", "_decomp.s",
		&(e->champ.assembly_name)))))
	{
		if (ret == -1)
			ft_printf("malloc error\n");
		else
			ft_printf("file must be of extension \'.cor\'\n");
		return (1);
	}
	return (ft_process_parse_cor(fd, e));
}
