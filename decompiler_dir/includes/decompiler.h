/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompiler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:52:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 17:48:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECOMPILER_H
# define DECOMPILER_H

# include "op.h"
# include "libft.h"
# include "champion.h"
# include "player.h"
# include <fcntl.h>
# include <stdio.h>

# define CHUNK_SIZE 4096

typedef struct		s_chunk
{
	int				size;
	char			buf[CHUNK_SIZE];
}					t_chunk;

typedef enum		e_phase
{
	HEADER,
	CODE
}					t_phase;

typedef struct		s_parser
{
	t_phase			phase;	
}					t_parser;

typedef struct		s_env
{
	t_player		player;
	t_champion		champ;
}					t_env;

int					ft_init_env(t_env *e, char *filename);
int					ft_parse_cor(char *filename, t_env *e);
int					get_next_chunk(int fd, t_chunk *chunk);
int					ft_encode_to_assembly(t_env *e);

#endif
