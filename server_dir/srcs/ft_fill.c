/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:50:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 16:17:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t	ft_memcpy_ret(void *dest, void *src, size_t size)
{
	ft_memcpy(dest, src, size);
	return (size);
}

int		ft_get_core_size_all(t_core *core)
{
	int size;

	size = 0;
	size += sizeof(t_name_size);
	size += sizeof(t_score_size);
	size += ft_strlen(core->name);
	return (size);
}

int		ft_get_data_size_all(t_server *server)
{
	int		size;
	t_list	*ptr;
	t_core	*core;

	size = 0;
	size += sizeof(t_flag);
	size += sizeof(t_nb_cores);
	ptr = server->cores;
	while (ptr != NULL)
	{
		size += ft_get_core_size_all(core);
		ptr = ptr->next;
	}
	return (size);
}

void	ft_add_size(void *content_core, char *data, int *size)
{
	t_core			*core;
	t_name_size		name_size;

	core = (t_core *)content_core;
	name_size = ft_strlen(core->name);
	*size += ft_memcpy_ret(&(data[*size]), &(name_size), sizeof(name_size));
	*size += ft_memcpy_ret(&(data[*size]), &(core->score), sizeof(core->score));
}

int		ft_send_all_cores(TCPsocket socket, t_server *server)
{
	char		*data;
	t_nb_cores	nb_cores;
	int			total_size;
	int			size;
	t_list		*ptr;

	server->flag = GET_ALL;
	total_size = ft_get_data_size_all(server);
	nb_champions = ft_lstlength(server->champions);
	if (!(data = (char *)(malloc(size))))
		return (1);
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &(server->flag), sizeof(server->flag));
	size += ft_memcpy_ret(&(data[size]), &(nb_cores), sizeof(nb_cores));
	ptr = server->cores;
	while (ptr != NULL)
	{
		ft_add_size_all(ptr->content, char *data, &size);
		ptr = ptr->next;
	}
	if (ft_send_protected(socket, data, size))
		return (1);
	return (0);
}
