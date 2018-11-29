/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:46:51 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/23 17:14:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_buffer_rest(t_list **list, int const fd)
{
	t_fd_buffer		*to_add;
	t_list			*ptr;
	t_list			*new_node;

	ptr = *list;
	while (ptr != NULL)
	{
		if (((t_fd_buffer *)(ptr->content))->fd == fd)
			return (((t_fd_buffer *)(ptr->content))->buffer);
		ptr = ptr->next;
	}
	if (!(to_add = (t_fd_buffer *)malloc(sizeof(t_fd_buffer))))
		return (NULL);
	to_add->fd = fd;
	if (!(new_node = ft_lstnew((void *)to_add, sizeof(to_add))))
		return (NULL);
	ft_lstadd(list, new_node);
	if (!(((t_fd_buffer *)((*list)->content))->buffer = ft_strnew(BUFF_SIZE)))
		return (NULL);
	free(to_add);
	return (((t_fd_buffer *)((*list)->content))->buffer);
}

int		ft_process_strcadline(int i, char **line, char *res, char *rest)
{
	int index;

	if (!(*line = ft_strsub(res, 0, i)))
		return (-1);
	i = 0;
	while (rest[i] != '\n')
		i++;
	index = i + 1;
	while (index < BUFF_SIZE)
	{
		rest[index - (i + 1)] = rest[index];
		index++;
	}
	rest[index - (i + 1)] = '\0';
	ft_strdel(&res);
	return (0);
}

int		ft_strcadline(char **line, char *rest, int *endline)
{
	char	*res;
	int		i;

	if (!(res = ft_strjoin(*line, rest)))
		return (-1);
	ft_strdel(line);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
	{
		if (ft_process_strcadline(i, line, res, rest) == -1)
			return (-1);
		*endline = 1;
	}
	else
	{
		if (!(*line = ft_strdup(res)))
			return (-1);
		ft_strdel(&res);
		ft_bzero(rest, BUFF_SIZE);
	}
	return (0);
}

int		process_get_next_line(int fd, char **line, int endline, char *rest)
{
	int ret;

	ret = 1;
	if (!endline)
	{
		ft_bzero(rest, BUFF_SIZE);
		while (!endline && (ret = read(fd, rest, BUFF_SIZE)) > 0)
		{
			if (ft_strcadline(line, rest, &endline) == -1)
				return (-1);
		}
		if (ret == -1)
			return (ret);
	}
	if (!ft_strcmp(*line, "") && ret == 0)
		return (0);
	else
		return (1);
}

int		get_next_line(int const fd, char **line)
{
	static t_list	*list = NULL;
	int				i;
	int				endline;
	char			*rest;
	int				index;

	if (line == NULL)
		return (-1);
	if (!(rest = ft_get_buffer_rest(&list, fd)))
		return (-1);
	endline = 0;
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		endline = 1;
	if (!(*line = ft_strndup(rest, i)))
		return (-1);
	index = i + 1;
	while (index < BUFF_SIZE)
	{
		rest[index - (i + 1)] = rest[index];
		index++;
	}
	return (process_get_next_line(fd, line, endline, rest));
}
