/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:44:18 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/15 14:36:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** free the node if it is not relevant anymore before returning ret
*/

int		ft_may_free_node(int ret, t_list **gnls, t_gnl *to_del)
{
	t_list *prev;
	t_list *current;

	if (ret == 0)
	{
		prev = NULL;
		current = *gnls;
		while (current != NULL)
		{
			if ((t_gnl *)current->content == to_del)
			{
				if (prev == NULL)
					*gnls = current->next;
				else
					prev->next = current->next;
				free(to_del->whole_buffer);
				free(to_del);
				free(current);
			}
			prev = current;
			current = current->next;
		}
	}
	return (ret);
}

/*
** get the rest of the "already read buffer" by previouses calls or create a
** new buffer for this particular fd and returns it
*/

t_gnl	*ft_get_gnl(int fd, t_list **gnls)
{
	t_list	*ptr;
	t_gnl	*to_add;
	t_list	*new_node;

	ptr = *gnls;
	while (ptr)
	{
		if (((t_gnl *)ptr->content)->fd == fd)
			return ((t_gnl *)ptr->content);
		ptr = ptr->next;
	}
	if (!(to_add = (t_gnl *)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	if (!(new_node = ft_lstnew_ptr(to_add, sizeof(t_list))))
	{
		free(to_add);
		return (NULL);
	}
	ft_lstadd(gnls, new_node);
	to_add->fd = fd;
	if (!(to_add->rest = ft_strnew(BUFF_SIZE)))
		return (NULL);
	to_add->whole_buffer = to_add->rest;
	return (to_add);
}

/*
** read until a newline is found and stock the rest of the buffer in
** the static node of get_next_line
*/

int		ft_process_gnl(int const fd, char **line, t_gnl *gnl)
{
	int			ret;
	int			new_line_index;
	int			readd;

	readd = (ft_strcmp(*line, "") == 0) ? 0 : 1;
	while (((ret = read(fd, gnl->rest, BUFF_SIZE)) > 0 &&
				((new_line_index = ft_strichr(gnl->rest, '\n')) == -1)))
	{
		readd = 1;
		gnl->rest[ret] = '\0';
		if (!(*line = ft_strjoin_free(*line, gnl->rest)))
			return (-1);
		ft_bzero(gnl->rest, BUFF_SIZE);
	}
	if (ret > 0)
	{
		readd = 1;
		gnl->rest[ret] = '\0';
		if (!(*line = ft_strnjoin_free(*line, gnl->rest, new_line_index)))
			return (-1);
		ft_strcpy(gnl->rest, &(gnl->rest[new_line_index + 1]));
	}
	return (ret == -1 ? -1 : readd);
}

/*
** get the first string in the "already read buffer" by previouses calls
** OR
** read more with ft_process_gnl (may also free the node if it became useless)
*/

int		get_next_line(int const fd, char **line)
{
	static t_list	*gnls = NULL;
	t_gnl			*gnl;
	int				i;
	int				ret;

	if (fd == -1 || line == NULL || (!(gnl = ft_get_gnl(fd, &gnls))))
		return (-1);
	i = 0;
	while (gnl->rest[i] && gnl->rest[i] != '\n')
		i++;
	if (!(*line = ft_strndup(gnl->rest, i)))
		return (-1);
	if (gnl->rest[i] == '\n')
	{
		gnl->rest += i + 1;
		return (1);
	}
	else
	{
		gnl->rest = gnl->whole_buffer;
		ft_bzero(gnl->rest, BUFF_SIZE);
		ret = ft_process_gnl(fd, line, gnl);
		return (ft_may_free_node(ret, &gnls, gnl));
	}
}
