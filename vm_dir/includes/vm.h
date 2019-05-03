/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/11 18:17:21 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "champion.h"
# include "player.h"
# include "errors.h"
# include "client.h"
# include "visu.h"
# include <fcntl.h>
# include "libft.h"

# define NB_TYPES	3

/*
** STANDARD COLORS (FOREGROUND)
*/

# define COLF_BLACK		"\033[22;30m"
# define COLF_RED		"\033[22;31m"
# define COLF_GREEN		"\033[22;32m"
# define COLF_BROWN		"\033[22;33m"
# define COLF_BLUE		"\033[22;34m"
# define COLF_MAGENTA	"\033[22;35m"
# define COLF_CYAN		"\033[22;36m"
# define COLF_GREY		"\033[22;37m"
# define COLF_BBLACK	"\033[01;30m"
# define COLF_BRED		"\033[01;31m"
# define COLF_BGREEN	"\033[01;32m"
# define COLF_BBROWN	"\033[01;33m"
# define COLF_BBLUE		"\033[01;34m"
# define COLF_BMAGENTA	"\033[01;35m"
# define COLF_BCYAN		"\033[01;36m"
# define COLF_BGREY		"\033[01;37m"
# define COLF_OFF		"\033[0m"
# define COL_CYCLES		COLF_BGREY
# define COL_DEATH		COLF_BBLACK
# define COL_RESIZE		COLF_BCYAN

typedef struct		s_process
{
	t_player		*player;
	t_instruction	pending_ins;
	int				live_cycle;
	unsigned int	reg[REG_NUMBER];
	int				pc;
	int				ins_bytelen;
	int				cycle;
	int				ins_cycle;
	unsigned char	carry;
	int				nb;
}					t_process;

typedef struct		s_metadata
{
	char			color_index;
	char			process_color_index;
	int				alt_color;
}					t_metadata;

typedef struct		s_fade
{
	int				pc;
	int				color;
	int				value;
}					t_fade;

typedef struct		s_display
{
	int				code;
	int				status;
}					t_display;

typedef struct		s_vm
{
	int				c_to_die;
	int				checks;
	int				win;
	int				cycle;
	t_display		display;
	int				total_cycle;
	int				nb_players;
	long long int	nb;
	char			**files;
	int				dump;
	t_visu			visu;
	t_client		client;
	char			arena[MEM_SIZE];
	t_metadata		metarena[MEM_SIZE];
	t_player		player[MAX_PLAYERS];
	t_player		local_player[MAX_PLAYERS];
	t_list			*proc;
	t_list			*killed_proc;
	t_list			*live_ok;
	int				live;
	int				issued_live;
	t_color_msg		color;
	t_player		*winner;
}					t_vm;

enum				e_return
{
	SUCCESS, FAILURE
};

enum				e_display
{
	OFF, ON
};

enum				e_console_display
{
	MSG_LIVE, MSG_CYCLE, MSG_INS, MSG_DEATH, MSG_MOVE, COLOR, MSG_AFF
};

/*
** DISPLAY AND COLOR
*/

void				display_player_intro(t_vm *vm, t_player *player);
void				display_player_alive(t_vm *vm, t_player *player);
void				display_cycle(t_vm *vm);
void				display_resize(t_vm *vm);
void				display_move(t_vm *vm, t_process *proc);
void				display_ins(t_vm *vm, t_process *proc);
void				display_last_live(t_vm *vm, t_process *proc);
void				display_winner(t_vm *vm);
void				display_registers(t_vm *vm);
void				display_proc_ins(t_vm *vm, t_process *proc);
int					error_exit_msg(t_vm *vm, const char *error);
void				set_colors_term(t_vm *vm);
int					set_color_sdl(t_vm *vm, t_player *player);
int					get_color_sdl(int index);

/*
** READ & PARSE
*/

int					check_type(int ac, char **av);
int					check_header(void);
int					corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
int					flags(t_vm *vm, int argc, char **argv);
int					read_files(t_vm *vm);

/*
** SET-UP AND CLEAR
*/

void				clear_vm(t_vm *vm);
void				init_vm(t_vm *vm, char **argv);
void				update_nb_players(t_vm *vm);
int					add_player(t_vm *vm);
int					add_player_n(t_vm *vm, int argc, char **argv, int *cur);

/*
** INSTRUCTIONS, LOADING AND STORING
*/

void				getval_param_dest(t_vm *vm, t_process *proc,
												t_parameter *arg, int mod);
int					ins_live(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_ld(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_st(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_add(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_sub(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_and(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_or(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_xor(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_zjmp(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_ldi(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_sti(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_fork(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_lld(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_lldi(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_lfork(t_vm *vm, t_process *proc, t_parameter arg[3]);
int					ins_aff(t_vm *vm, t_process *proc, t_parameter arg[3]);
void				load_arena(t_vm *vm, t_process *proc, int index, int val);
void				load_reg(t_vm *vm, t_process*proc, int num, int val);
int					no_ins(t_vm *vm, t_process *proc, t_parameter arg[3]);

/*
** PLAY
*/

void				dispatch_players_init(t_vm *vm);
void				dump(t_vm *vm);
t_list				*add_process(t_vm *vm, int i, int start, t_process *src);
int					kill_process(t_vm *vm, t_list **proc);
int					kill_process_at_head(t_vm *vm);
int					init_processes(t_vm *vm);
int					play_one_cycle(t_vm *vm);

/*
** UTILS
*/

int					mod(int val, int max);

/*
** process visual loop and events
*/

int					process_visu(t_vm *vm);

/*
** client connection to scorewar
*/

int					process_client(t_vm *vm);
int					fight_cores(t_vm *vm, t_player *pl1, t_player *pl2);

#endif
