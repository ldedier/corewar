/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/05 18:50:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_print_usage(char *name)
{
	ft_printf("%s [port (ex: 3001)]\n", name);
	return (1);
}

void	ft_init_client_socket(t_client_socket *cs)
{
	cs->socket = NULL;
	cs->isfree = 1;
	cs->player_number = -1;
}

int		ft_init_server(int argc, char **argv, t_server *server)
{
	int i;

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
	while (i < MAX_PLAYERS)
	{
		ft_init_client_socket(&(server->client_sockets[i]));
		i++;
	}
	server->nb_players = 0;
	server->message.flag = STANDARD;
	server->running = 1;
	return (0);
}

int		ft_init_db(t_server *server)
{
	server->champions = NULL;
	return (0);
}

int main(int argc, char **argv)
{
	t_server server;

	if (SDLNet_Init() == -1)
		return ft_error();
	if (ft_init_server(argc, argv, &server))
		return (1);
	if (ft_init_db(&server))
		return (1);
	ft_printf(GREEN"server successfuly deployed on port %d!\n\n"EOC,
			server.port);
	ft_printf("%s\n", ACTIVITY_SRCH);
	if (ft_process_server(&server))
		return (1);
	return (0);
}
