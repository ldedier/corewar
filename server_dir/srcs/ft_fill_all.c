/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:48:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 22:02:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_get_core_size_all(t_core *core)
{
	int size;

	size = 0;
	size += sizeof(t_score);
	size += sizeof(t_name_size);
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
		core = (t_core *)(ptr->content);
		size += ft_get_core_size_all(core);
		ptr = ptr->next;
	}
	return (size);
}

void	ft_add_core_data_all(void *content_core, char *data, int *size)
{
	t_core			*core;
	t_name_size		name_size;

	core = (t_core *)content_core;
	name_size = ft_strlen(core->name);
	*size += ft_memcpy_ret(&(data[*size]), &(core->score), sizeof(core->score));
	*size += ft_memcpy_ret(&(data[*size]), &(name_size), sizeof(name_size));
	*size += ft_memcpy_ret(&(data[*size]), core->name, name_size);
}

int		ft_send_all_cores(TCPsocket socket, t_server *server)
{
	char		*data;
	t_nb_cores	nb_cores;
	int			total_size;
	int			size;
	t_list		*ptr;

	server->flag = GET_LIST;
	total_size = ft_get_data_size_all(server);
	nb_cores = ft_lstlength(server->cores);
	if (!(data = (char *)(malloc(total_size))))
		return (1);
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &(server->flag), sizeof(server->flag));
	size += ft_memcpy_ret(&(data[size]), &(nb_cores), sizeof(nb_cores));
	ptr = server->cores;
	while (ptr != NULL)
	{
		ft_add_core_data_all(ptr->content, data, &size);
		ptr = ptr->next;
	}
	if (ft_send_protected(socket, data, size))
		return (1);
	return (0);
}
