/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/31 16:39:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# include <stdlib.h>
# include "libft.h"
# define MAX_TCP_PACKET		10000

typedef int				t_nb_players;
typedef char			t_player_number;

typedef enum			e_flag
{
	CONNECTION,
	DISCONNECTION,
	LOGGED,
	SERVER_FULL,
	GET_LIST,
	GET_CORE,
	FLAG_UPLOAD,
	FLAG_DOWNLOAD,
	UPLOAD_NAME_TAKEN,
	FLAG_NEW_CORE
}						t_flag;

size_t					ft_memcpy_ret(void *dest, void *src, size_t size);
void					ft_memcpy_recv(void *dest, void *src, int *index,
							size_t size);
#endif
