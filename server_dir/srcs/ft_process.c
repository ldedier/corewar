/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:50:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 17:50:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_process_data(t_server *server, int i, int nb_bytes)
{
	t_flag flag;

	ft_printf("data received !\n");
	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	ft_memcpy(&flag, server->buffer, sizeof(t_flag));
	if (flag == GET_CORE)
		return (ft_send_core(server, i, nb_bytes));
	if (flag == GET_CORE_BIN)
		return (ft_send_core_bin(server, i, nb_bytes));
	if (flag == FLAG_UPLOAD)
		return (ft_receive_upload(server, i, nb_bytes));
	return (0);
}

int		ft_process_player_activity(t_server *server, int i)
{
	int nb_bytes;

	if (SDLNet_SocketReady(server->client_sockets[i].socket) != 0)
	{
		if ((nb_bytes = SDLNet_TCP_Recv(server->client_sockets[i].socket,
			server->buffer, MAX_TCP_PACKET)) <= 0)
		{
			if (ft_disconnect_player(server, i))
				return (1);
		}
		else
		{
			if (ft_process_data(server, i, nb_bytes))
				return (1);
		}
	}
	return (0);
}

int		ft_process_activity(t_server *server)
{
	int i;

	if (SDLNet_SocketReady(server->socket))
	{
		if (ft_attempt_connection(server))
			return (1);
	}
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ft_process_player_activity(server, i))
			return (1);
		i++;
	}
	return (0);
}

int		ft_process_server(t_server *server)
{
	while (server->running)
	{
		if (SDLNet_CheckSockets(server->socket_set, 1000) <= 0)
			ft_printf("%s\n", ACTIVITY_SRCH);
		else
		{
			if (ft_process_activity(server))
				return (1);
		}
	}
	return (0);
}
