/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/07 01:16:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# include <stdlib.h>
# include "libft.h"
# define MAX_TCP_PACKET		10000

typedef int				t_name_size;
typedef int				t_comment_size;
typedef int				t_code_size;
typedef int				t_nb_cores;
typedef int				t_score;
typedef char			t_player_number;

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
	t_score				score;
}						t_core;

t_core					*ft_new_core(char *name, t_score score);
void					ft_print_core(t_core *core);
void					ft_print_cores(t_list *cores);
#endif
