/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/08 18:18:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include "champion.h"
//# include "color.h"
//# include "visu.h"
//# include "client.h"
# include <fcntl.h>
# define TOT_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)
# define DEAD		-100
# define NEEDS_OCP	60925

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
	int				header_size;
	int				file_len;
	int				algo_len;
	int				num;
	char			*cor_name;
}					t_player;

typedef struct		s_color
{
	char			player[MAX_PLAYERS * 2][10];
	
	
}			t_color;

typedef struct		s_process
{
	int				id;
	int				live;
	unsigned char	reg[REG_NUMBER];
	int				pc;
	int				cycle;
	unsigned char	carry;
}
					t_process;
typedef struct		s_live
{
	int	nb;
	int	total_pl;
	int	last_pl;
}			t_live;



typedef struct		s_vm
{
	int				c_to_die;
	int				max_checks;
	int				win;
	int				nb_players;
	char			**files;
	int				dead;
	int				dump;
	t_color				color;
//	t_client		client;
//	t_visu			visu;
	t_arena			arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS + 1];
	t_process		*proc;
	t_live			live;
}					t_vm;

enum				e_return
{
	SUCCESS, FAILURE
};

enum				e_arg
{
	FIRST, SECOND, THIRD
};


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

/*
** INSTRUCTIONS
*/

int					ins_live(t_vm *vm, t_parameter arg[3], int pl);
int					ins_ld(t_vm *vm, t_parameter arg[3], int pl);
int					ins_st(t_vm *vm, t_parameter arg[3], int pl);
int					ins_add(t_vm *vm, t_parameter arg[3], int pl);
int					ins_sub(t_vm *vm, t_parameter arg[3], int pl);
int					ins_and(t_vm *vm, t_parameter arg[3], int pl);
int					ins_or(t_vm *vm, t_parameter arg[3], int pl);
int					ins_xor(t_vm *vm, t_parameter arg[3], int pl);
int					ins_zjmp(t_vm *vm, t_parameter arg[3], int pl);
int					ins_ldi(t_vm *vm, t_parameter arg[3], int pl);
int					ins_sti(t_vm *vm, t_parameter arg[3], int pl);
int					ins_fork(t_vm *vm, t_parameter arg[3], int pl);
int					ins_lld(t_vm *vm, t_parameter arg[3], int pl);
int					ins_lldi(t_vm *vm, t_parameter arg[3], int pl);
int					ins_lfork(t_vm *vm, t_parameter arg[3], int pl);
int					ins_aff(t_vm *vm, t_parameter arg[3], int pl);

/*
** PLAY
*/

void				check_resize_cycle(t_vm *vm, int *cycle);
int				play(t_vm *vm);
void				launch_instruction(t_vm *vm, int player);


/*
** UTILS
*/

int					mod(int val, int max);
int					ft_pow(int n, int pow);

// TEMP delete at end
void				display_arena(t_arena *arena); //tmp for test and debug
void				test_ins(t_vm *vm);
void				set_processes(t_vm *vm, t_process **proc);

int					process_client(t_vm *vm);

#endif
