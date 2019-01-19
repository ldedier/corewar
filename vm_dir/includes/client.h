/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:26:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 18:16:27 by ldedier          ###   ########.fr       */
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
int						ft_query_player_size(t_player *player);
int						ft_free_all_client(t_client *client);
int						ft_process_client_events(t_vm *vm);
t_client_slot			*get_client_slot(t_vm *vm, char *name);
t_client_slot			*ft_new_client_slot(t_vm *vm, t_player *player);
int						ft_process_add_client_slots(int nb_bytes, t_vm *vm);
int						ft_process_new_client_slot(t_vm *vm, int i,
							t_name_len name_len, t_score score);
void					ft_populate_download_button(t_vm *vm,
							t_client_slot *client_slot, t_button *button);
int						ft_receive_connect_status(t_vm *vm);
#endif
