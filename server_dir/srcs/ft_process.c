/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:50:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/04 20:38:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_send_protected(TCPsocket socket, void *data, size_t size)
{
	if (SDLNet_TCP_Send(socket, data, size) < (int)size)
		return (1);
	return (0);
}

int		ft_accept_player(t_server *server)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (server->client_sockets[i].isfree == 1)
		{
			server->client_sockets[i].isfree = 0;
			break;
		}
		i++;
	}
	if (!(server->client_sockets[i].socket = SDLNet_TCP_Accept(server->socket)))
		return (1);
	if (SDLNet_TCP_AddSocket(server->socket_set,
			server->client_sockets[i].socket) == -1)
		return (1);
	server->message.flag = LOGGED;
	if (ft_send_protected(server->client_sockets[i].socket, &(server->message),
				sizeof(server->message)))
		return (ft_error());
	server->nb_players++;
	return (0);
}

int		ft_deny_player(t_server *server)
{
	TCPsocket temp;

	if(!(temp = SDLNet_TCP_Accept(server->socket)))
		return (ft_error());
	server->message.flag = SERVER_FULL;
	if (ft_send_protected(temp, &(server->message), sizeof(server->message)))
		return (ft_error());
	SDLNet_TCP_Close(temp);
	return (0);
}

int		ft_attempt_connection(t_server *server)
{
	if (server->nb_players < MAX_PLAYERS)
		return (ft_accept_player(server));
	else
		return (ft_deny_player(server));
}

int		ft_disconnect_player(t_server *server, int i)
{
	int j;

	SDLNet_TCP_DelSocket(server->socket_set, server->client_sockets[i].socket);
	SDLNet_TCP_Close(server->client_sockets[i].socket);
	server->nb_players--;
	server->message.player_number = server->client_sockets[i].player_number;
	server->message.flag = DISCONNECTION;
	ft_init_client_socket(&(server->client_sockets[i]));
	j = 0;
	while (i < MAX_PLAYERS)
	{
		if (!server->client_sockets[j].isfree)
		{
			if (ft_send_protected(server->client_sockets[j].socket,
					&(server->message), sizeof(server->message)))
			return (ft_error());
		}
		i++;
	}
	return (0);
}

int		ft_process_data(t_server *server)
{
	(void)server;
	ft_printf("on a recu !\n");
	return (0);
}

int		ft_process_player_activity(t_server *server, int i)
{
	if (SDLNet_SocketReady(server->client_sockets[i].socket) != 0)
	{
		if (SDLNet_TCP_Recv(server->client_sockets[i].socket,
				&(server->received), sizeof(server->received)) <= 0)
		{
			if (ft_disconnect_player(server, i))
				return (1);
		}
		else
		{
			if (ft_process_data(server))
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
	while (i <  MAX_PLAYERS)
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
