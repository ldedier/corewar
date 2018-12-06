/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:20:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 16:03:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <SDL2_net/SDL_net.h>
# include <SDL2/SDL.h>
# include "libft.h"
# include "op.h"
# include "network.h"

# define MAX_SOCKETS	MAX_PLAYERS + 1
# define ACTIVITY_SRCH	"server is looking for activity..."

typedef struct			s_client_socket
{
	TCPsocket			socket;
	char				isfree;
	char				player_number;
}						t_client_socket;

typedef struct			s_server
{
	IPaddress			ip;
	TCPsocket			socket;
	int					port;
	t_client_socket		client_sockets[MAX_PLAYERS];
	SDLNet_SocketSet	socket_set;
	t_server_message	message;
	t_client_message	received;
	int					nb_players;
	int					running;
	t_flag				flag;
	t_list				*cores;
}						t_server;

int						ft_process_server(t_server *server);
int						ft_error(void);
int						ft_send_protected(TCPsocket socket, void *data,
							size_t size);
void					ft_init_client_socket(t_client_socket *cs);
#endif
