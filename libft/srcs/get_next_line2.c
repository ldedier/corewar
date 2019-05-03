/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 03:46:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/14 20:43:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strichr_gnl_separator(char *buffer, int buffer_len)
{
	int i;

	i = 0;
	while (i < buffer_len)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

/*
** read until a newline or 0 is found and stock the rest of the buffer in
** the static node of get_next_line
*/

int		ft_process_gnl2(int const fd, t_gnl_info *info, t_gnl *gnl)
{
	int			ret;
	int			nl_index;
	int			readd;

	readd = (ft_strcmp(info->line, "") == 0) ? 0 : 1;
	while (((ret = read(fd, gnl->rest, BUFF_SIZE)) > 0
			&& ((nl_index = ft_strichr_gnl_separator(gnl->rest, ret)) == -1)))
	{
		readd = 1;
		gnl->rest[ret] = '\0';
		if (!(info->line = ft_strjoin_free(info->line, gnl->rest)))
			return (-1);
		ft_bzero(gnl->rest, BUFF_SIZE);
	}
	if (ret > 0)
	{
		readd = 1;
		gnl->rest[ret] = '\0';
		info->separator = gnl->rest[nl_index];
		if (!(info->line = ft_strnjoin_free(info->line, gnl->rest, nl_index)))
			return (-1);
		ft_strcpy(gnl->rest, &(gnl->rest[nl_index + 1]));
		gnl->size = ret - nl_index - 1;
	}
	return (ret == -1 ? -1 : readd);
}

int		get_already_read_buffer(t_gnl *gnl, t_gnl_info *info)
{
	int		i;

	i = 0;
	while (gnl->size && gnl->rest[i] != '\n' && gnl->rest[i] != '\0')
	{
		gnl->size--;
		i++;
	}
	if (!(info->line = ft_strndup(gnl->rest, i)))
		return (-1);
	if (gnl->size)
	{
		info->separator = gnl->rest[i];
		gnl->rest += i + 1;
		gnl->size--;
		return (1);
	}
	return (0);
}

/*
** get the first string in the "already read buffer" by previouses calls
** OR
** read more with ft_process_gnl2 (may also free the node if it became useless)
*/

int		get_next_line2(int const fd, t_gnl_info *info)
{
	static t_list	*gnls = NULL;
	t_gnl			*gnl;
	int				ret;

	info->separator = EOF;
	if (fd == -1 || (!(gnl = ft_get_gnl(fd, &gnls))))
		return (-1);
	if ((ret = get_already_read_buffer(gnl, info)))
		return (ret);
	else
	{
		gnl->rest = gnl->whole_buffer;
		ft_bzero(gnl->rest, BUFF_SIZE);
		ret = ft_process_gnl2(fd, info, gnl);
		return (ft_may_free_node(ret, &gnls, gnl));
	}
}
