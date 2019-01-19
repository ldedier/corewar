/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_core_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:58:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 17:15:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_send_core_bin_packet_size(t_player *player)
{
	int size;

	size = 0;
	size += sizeof(t_flag);
	size += sizeof(t_file_len);
	size += player->file_len;
	return (size);
}

int		ft_process_send_core_bin(t_server *server, t_player *player, int i)
{
	int		total_size;
	char	*data;
	int		size;

	total_size = ft_send_core_bin_packet_size(player);
	if (!(data = (char *)malloc(total_size)))
		return (1);
	server->flag = GET_CORE_BIN;
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &server->flag, sizeof(t_flag));
	size += ft_memcpy_ret(&(data[size]), &player->file_len, sizeof(t_file_len));
	size += ft_memcpy_ret(&(data[size]), &player->bin, player->file_len);
	if (ft_send_protected(server->client_sockets[i].socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}

int		ft_send_core_bin(t_server *server, int i, int nb_bytes)
{
	t_player *player;

	if (!(player = get_core_from_query(server, nb_bytes)))
		return (1);
	return (ft_process_send_core_bin(server, player, i));
}
