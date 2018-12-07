/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:26:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 16:22:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <SDL2_net/SDL_net.h>
# include "network.h"

# define NB_CONNECTION_RETRIES	5

typedef struct			s_client
{
	char				active;
	int					port;
	char				*server_address;
	TCPsocket			socket;
	IPaddress			server_ip;
	SDLNet_SocketSet	socket_set;
	char				running;
	t_client_message	message;
	t_server_message	received;
	t_list				*cores;
	t_flag				flag;
}						t_client;

int						ft_net_error(void);
int						ft_send_protected(TCPsocket socket, void *data,
							size_t size);

#endif
