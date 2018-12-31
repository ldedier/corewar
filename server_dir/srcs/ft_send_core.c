/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 22:50:09 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/31 17:59:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_player *get_core_from_query(t_server *server, int nb_bytes)
{
	t_player	*player;
	char		*name;
	int			i;
	int			name_len;

	(void)nb_bytes; //OLALALA
	i = sizeof(t_flag);
	name_len = (t_name_len)server->buffer[i];
	i += sizeof(t_name_len);
	if (!(name = ft_strndup(&(server->buffer[i]), name_len)))
		return (NULL);
	if (!(player = get_player(server, name)))
	{
		ft_putendl(name);
		free(name);
		return (NULL);
	}
	return (player);
}

int		ft_send_core_packet_size(t_player *player)
{
	int size = 0;

	size += sizeof(t_flag);
	size += sizeof(t_comment_len);
	size += player->comm_len;
	size += sizeof(t_code_len);
	size += player->algo_len;
	return (size);
}

int		ft_process_send_core(t_server *server, t_player *player, int i)
{
	int		total_size;
	char	*data;
	int		size;

	total_size = ft_send_core_packet_size(player);
	if (!(data = (char *)malloc(total_size)))
		return (1);
	server->flag = GET_CORE;
	size = 0;

	size += ft_memcpy_ret(&(data[size]), &server->flag, sizeof(t_flag));
	size += ft_memcpy_ret(&(data[size]), &player->comm_len, sizeof(t_comment_len));
	size += ft_memcpy_ret(&(data[size]), &player->comm, player->comm_len);
	size += ft_memcpy_ret(&(data[size]), &player->algo_len, sizeof(t_code_len));
	size += ft_memcpy_ret(&(data[size]), &player->algo, player->algo_len);
	if (ft_send_protected(server->client_sockets[i].socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}

int		ft_send_core(t_server *server, int i, int nb_bytes)
{
	t_player *player;
	if (!(player = get_core_from_query(server, nb_bytes)))
		return (1);
	return (ft_process_send_core(server, player, i));
}
