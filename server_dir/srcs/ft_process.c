/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:50:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 21:27:04 by ldedier          ###   ########.fr       */
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
	if (ft_send_all_cores(server->client_sockets[i].socket, server))
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

t_player *get_core_from_query(t_server *server)
{
	t_player	*player;
	char		*name;
	int			i;
	int			name_len;

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

int		ft_send_core(t_server *server, int i)
{
	t_player *player;
	if (!(player = get_core_from_query(server)))
		return (1);
	return (ft_process_send_core(server, player, i));
}

int		ft_process_data(t_server *server, int i)
{
	(void)server;
	ft_printf("on a recu !\n");
	if ((t_flag)server->buffer[0] == GET_CORE)
		return (ft_send_core(server, i));
	
	return (0);
}

int		ft_process_player_activity(t_server *server, int i)
{
	if (SDLNet_SocketReady(server->client_sockets[i].socket) != 0)
	{
		if (SDLNet_TCP_Recv(server->client_sockets[i].socket,
			server->buffer, MAX_TCP_PACKET) <= 0)
		{
			if (ft_disconnect_player(server, i))
				return (1);
		}
		else
		{
			if (ft_process_data(server, i))
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
