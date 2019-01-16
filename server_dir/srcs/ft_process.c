/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:50:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/12 10:14:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
	if (ft_send_all_cores(server->client_sockets[i].socket, server, GET_LIST))
		return (ft_error());
	server->nb_players++;
	ft_printf("connect: %d\n", server->nb_players);
	return (0);
}

int		ft_deny_player(t_server *server)
{
	TCPsocket temp;

	if (!(temp = SDLNet_TCP_Accept(server->socket)))
		return (ft_error());
	if (ft_send_rejection(temp))
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
	ft_printf("disconnect: %d\n", server->nb_players);
	ft_init_client_socket(&(server->client_sockets[i]));
	j = 0;
	/*
	while (i < MAX_PLAYERS)
	{
		if (!server->client_sockets[j].isfree)
		{
			if (ft_send_deconnexion(server->client_sockets[j].socket, 
				server->client_sockets[i].player_number))
					return (ft_error());
		}
		i++;
	}
	*/
	return (0);
}

t_player 	*get_player(t_server *server, char *name)
{
	t_list		*ptr;
	t_player	*player;

	ptr = server->players;
	while (ptr != NULL)
	{
		player = ptr->content;
		if (!ft_strcmp(player->name, name))
			return (player);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_process_data(t_server *server, int i, int nb_bytes)
{
	t_flag flag;

	ft_printf("on a recu !\n");
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
