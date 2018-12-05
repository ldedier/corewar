/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/05 17:01:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# define CHUNK_SIZE		1000

typedef enum			e_flag
{
	STANDARD,
	DISCONNECTION,
	LOGGED,
	SERVER_FULL
}						t_flag;

typedef struct			s_client_message
{
	char				chunk[CHUNK_SIZE];
	char				is_last;
}						t_client_message;

typedef struct			s_server_message
{
	char				chunk[CHUNK_SIZE];
	char				player_number;
	char				is_last;
	t_flag				flag;
}						t_server_message;

#endif
