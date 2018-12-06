/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 16:22:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# define CHUNK_SIZE		1000

typedef int				t_name_size;
typedef int				t_score_size;
typedef int				t_comment_size;
typedef int				t_code_size;
typedef int				t_nb_cores;

typedef enum			e_flag
{
	CONNECTION,
	DISCONNECTION,
	LOGGED,
	SERVER_FULL,
	GET_LIST,
	GET_CORE
}						t_flag;

typedef struct			s_source_code
{
	t_code_size			size;
	char				*bytes;
}						t_source_code;

typedef struct          s_core
{
	char				*name;
	char				*comment;
	t_source_code		code;
	t_score_size		score;
}						t_core;

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
