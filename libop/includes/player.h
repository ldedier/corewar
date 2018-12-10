/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:25:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/07 22:25:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "op.h"
# include "libft.h"
# include <fcntl.h>

# define FILE_TOO_BIG	"Size of the given file is too large to be handled"
# define INVALID_CHARS	"Incorrect characters were used in the .cor file"
# define MAX_CHAMP		"Given champion is too large to be handled"
# define WRG_HEAD_SIZE	"Header size does not match file's code size"
# define TOT_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

typedef int				t_name_len;
typedef int				t_comment_len;
typedef int				t_code_len;
typedef int				t_score;

typedef struct      s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comm[COMMENT_LENGTH + 1];
	char			algo[CHAMP_MAX_SIZE + 1];
	char			bin[TOT_SIZE + 1];
	t_comment_len	comm_len;
	t_name_len		name_len;
	t_code_len		algo_len;
	t_score			score;
	int				header_size;
	int				file_len;
	int				num;
	char			*cor_name;
}					t_player;

int					ft_read_player(char *path, t_player *player);
int					ft_process_read_player(char *data, int length,
						t_player *player);
int					ft_parse_player(t_player *player);
t_player			*ft_new_player(char *name, t_name_len len, t_score score);
int					ft_return_verbosed(char *str, int ret);
void				ft_print_players(t_list *players);
void				ft_print_player(t_player *player);
#endif