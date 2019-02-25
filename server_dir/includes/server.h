/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:20:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 17:12:35 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <SDL2_net/SDL_net.h>
# include <SDL2/SDL.h>
# include "libft.h"
# include "op.h"
# include "network.h"
# include "player.h"
# include "vm.h"
# include <dirent.h>
# include <sys/stat.h>
# define MAX_SOCKETS	MAX_PLAYERS + 1
# define ACTIVITY_SRCH	"server is looking for activity..."

typedef struct			s_client_socket
{
	TCPsocket			socket;
	char				isfree;
	t_player_number		player_number;
}						t_client_socket;

typedef struct			s_server
{
	IPaddress			ip;
	TCPsocket			socket;
	int					port;
	t_client_socket		client_sockets[MAX_PLAYERS];
	SDLNet_SocketSet	socket_set;
	int					nb_players;
	int					running;
	char				buffer[MAX_TCP_PACKET];
	t_flag				flag;
	t_list				*players;
	t_vm				vm;
}						t_server;

int						fight_cores(t_vm *vm, t_player *pl1, t_player *pl2);
int						ft_print_usage(char *progname);
int						ft_init_server(int argc, char **argv, t_server *server);
void					ft_init_client_socket(t_client_socket *cs);
int						ft_init_db(t_server *server);
int						ft_process_server(t_server *server);

int						ft_error(void);
int						ft_send_protected(TCPsocket socket, void *data,
							size_t size);
size_t					ft_memcpy_ret(void *dest, void *src, size_t size);
int						ft_send_all_cores(TCPsocket socket, t_server *server,
							t_flag flag);
int						ft_send_rejection(TCPsocket temp);
int						ft_send_deconnexion(TCPsocket socket,
							t_player_number player_number);
int						ft_send_core(t_server *server, int i, int nb_bytes);
t_player				*get_player(t_server *server, char *name);
int						ft_receive_upload(t_server *server, int i,
							int nb_bytes);
int						ft_get_player_size_all(t_player *player);
int						ft_send_core_bin(t_server *server, int i, int nb_bytes);
t_player				*get_core_from_query(t_server *server, int nb_bytes);
char					*ft_get_buffer_all_cores(t_server *server, t_flag flag,
							int *size);
int						ft_attribute_scores_init(t_server *server);
void					ft_process_score(t_server *server);
int						ft_send_flag(t_server *server, int client_index,
							t_flag flag);
int						ft_attempt_connection(t_server *server);
int						ft_disconnect_player(t_server *server, int i);
#endif
