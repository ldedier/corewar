/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:42:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 18:51:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_init_client_socket(t_client_socket *cs)
{
	cs->socket = NULL;
	cs->isfree = 1;
}

int		ft_init_server(int argc, char **argv, t_server *server)
{
	int i;

	ft_bzero(server, sizeof(t_server));
	if (argc < 2)
		return (ft_print_usage(argv[0]));
	server->port = ft_atoi(argv[1]);
	if (SDLNet_ResolveHost(&(server->ip), NULL, server->port) == -1)
		return (ft_error());
	if (!(server->socket = SDLNet_TCP_Open(&(server->ip))))
		return (ft_error());
	if (!(server->socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS)))
		return (ft_error());
	if (SDLNet_TCP_AddSocket(server->socket_set, server->socket) == -1)
		return (ft_error());
	i = 0;
	while (i < MAX_CLIENTS)
	{
		ft_init_client_socket(&(server->client_sockets[i]));
		i++;
	}
	server->nb_players = 0;
	server->running = 1;
	init_vm(&server->vm, argv);
	return (0);
}
