/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/06 15:18:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			ft_accept_player(t_server *server)
{
	int i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (server->client_sockets[i].isfree == 1)
		{
			server->client_sockets[i].isfree = 0;
			break ;
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
	ft_printf("connected player (%d)\n", server->nb_players);
	return (0);
}

int			ft_deny_player(t_server *server)
{
	TCPsocket temp;

	if (!(temp = SDLNet_TCP_Accept(server->socket)))
		return (ft_error());
	if (ft_send_rejection(temp))
		return (ft_error());
	SDLNet_TCP_Close(temp);
	return (0);
}

int			ft_attempt_connection(t_server *server)
{
	if (server->nb_players < MAX_CLIENTS)
		return (ft_accept_player(server));
	else
		return (ft_deny_player(server));
}

int			ft_disconnect_player(t_server *server, int i)
{
	SDLNet_TCP_DelSocket(server->socket_set, server->client_sockets[i].socket);
	SDLNet_TCP_Close(server->client_sockets[i].socket);
	server->nb_players--;
	ft_printf("disconnected player (%d)\n", server->nb_players);
	ft_init_client_socket(&(server->client_sockets[i]));
	return (0);
}

t_player	*get_player(t_server *server, char *name)
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
