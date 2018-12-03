/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/11/23 16:42:17 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H

# include "../../libft/inc/libft.h"
# include "../../libop/includes/op.h"

# define TOT_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

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
	int				num;
	int				prog;
}					t_player;

typedef struct		s_vm
{
	int				c_to_die;
	int				win;
	int				nb_players;
	char			**files;
	int				dump;
	t_arena			arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS + 1];
}					t_vm;

void				error_exit(int n);
void				error_exit2(int n);
int					check_type(int ac, char **av);
void				init_vm(t_vm *vm, char **argv);
void				flags(t_vm *vm, int argc, char **argv);
void				read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);

#endif
