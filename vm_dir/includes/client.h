/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:26:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/16 19:05:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <SDL2_net/SDL_net.h>
# include "network.h"
# include "player.h"
# include "visu.h"

typedef struct s_vm		t_vm;

typedef struct			s_client_slot
{
	t_player			*player;
	t_button			download;
	char				downloaded;
	char				on_disk;
}						t_client_slot;

typedef struct			s_client
{
	char				active;
	int					port;
	char				*server_address;
	TCPsocket			socket;
	IPaddress			server_ip;
	SDLNet_SocketSet	socket_set;
	char				running;
	char				buffer[MAX_TCP_PACKET];
	t_list				*client_slots;
	t_player			upload_player;
	t_flag				flag;
}						t_client;

int						ft_query_player(t_vm *vm, t_client_slot *cs);
int						ft_net_error(void);
int						ft_send_protected(TCPsocket socket, void *data,
							size_t size);
int						ft_process_client_events(t_vm *vm);
#endif
