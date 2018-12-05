/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/05 18:30:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include "champion.h"
# include "visu.h"
# include "client.h"
# include <fcntl.h>
# define TOT_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

# define INVALID_PORT	"invalid port for the corehub server"
# define INSUF_INFO_CH	"port and address of the corehub server are needed"

typedef struct		s_arena
{
	char			hex;
}					t_arena;

typedef struct		s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comm[COMMENT_LENGTH + 1];
	char			algo[CHAMP_MAX_SIZE + 1];
	char			bin[TOT_SIZE + 1];
	int				file_len;
	int				algo_len;
	int				num;
	char			*cor_name;
}					t_player;

typedef struct		s_vm
{
	int				c_to_die;
	int				win;
	int				nb_players;
	char			**files;
	int				dump;
	t_client		client;
	t_visu			visu;
	t_arena			arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS + 1];
}					t_vm;


void				test(t_vm vm);
void				ft_error_exit(const char *error);
void				error_exit(int n);
void				error_exit2(int n);
int					check_type(int ac, char **av);
void				init_vm(t_vm *vm, char **argv);
void				corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
void				flags(t_vm *vm, int argc, char **argv);
void				read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);
void				dispatch_players(t_vm *vm);

int					process_client(t_vm *vm);

#endif
