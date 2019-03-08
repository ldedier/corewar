/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:47:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 18:53:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		ft_free_player(t_player *player)
{
	ft_lstdel_ptr(&player->beaten_players);
	free(player);
}

void		free_player_lst(void *p, size_t dummy)
{
	t_player *player;

	(void)dummy;
	player = (t_player *)p;
	ft_free_player(player);
}

void		ft_free_all_server(t_server *server)
{
	int i;

	ft_lstdel(&server->players, free_player_lst);
	if (server->socket)
		SDLNet_TCP_Close(server->socket);
	if (server->socket_set)
		SDLNet_FreeSocketSet(server->socket_set);
	clear_vm(&server->vm);
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (!server->client_sockets[i].isfree)
		{
			if (server->client_sockets[i].socket)
				SDLNet_TCP_Close(server->client_sockets[i].socket);
			server->client_sockets[i].socket = NULL;
			server->client_sockets[i].isfree = 1;
		}
		i++;
	}
}

int			exit_server(t_server *server, int ret)
{
	ft_free_all_server(server);
	return (reset_shell(ret));
}
