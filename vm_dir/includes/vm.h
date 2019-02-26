/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/26 21:09:20 by emuckens         ###   ########.fr       */
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

typedef struct		s_pending
{
	t_instruction	ins;
	void			*dest;
	int				dest_index;
	long				value;
	int				pc;
	int				cycles;
}					t_pending;

typedef struct		s_process
{
	t_player		*player;
	t_instruction	pending_ins;
	int				live;
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

typedef struct		s_color_term
{
	char 			cycle[11];
	char			death[11];
	char			resize[11];
}					t_color_term;

typedef struct		s_vm
{
	int				c_to_die;
	int				checks;
	int				win;
	int				cycle;
	int				display;
	int				total_cycle;
	int				nb_players;
	long long int	nb;
	char			**files;
	int				dump;
	char			color[MAX_PL_COLOR];
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
	t_color_term	col;
	t_player		*winner;
}					t_vm;

enum				e_return
{
	SUCCESS, FAILURE
};

enum				e_arg
{
	FIRST, SECOND, THIRD
};

enum				e_console_display
{
	MSG_LIVE, MSG_CYCLE, MSG_INS, MSG_DEATH, MSG_MOVE, COLOR
};

void				load_arena(t_vm *vm, t_process *proc, int index, int val);
void				load_reg(t_vm *vm, t_process*proc, int num, int val);
t_list				*add_process(t_vm *vm, int index, int start, t_process *src);


int					fight_cores(t_vm *vm, t_player *pl1, t_player *pl2);
int					error_exit_msg(t_vm *vm, const char *error);
int					check_type(int ac, char **av);
int					check_header(t_vm *vm);
void				init_vm(t_vm *vm, char **argv);
void				clear_vm(t_vm *vm);
int					corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
int					flags(t_vm *vm, int argc, char **argv);
int					read_files(t_vm *vm);
int					parse(t_vm *vm);
void				init_players(t_vm *vm);
void				dispatch_players_init(t_vm *vm);
int					init_processes(t_vm *vm);
void				init_local_players(t_vm *vm);
void				update_nb_players(t_vm *vm);
void				update_buttons(t_vm *vm);
t_player			*duel(t_vm *vm, t_player *pl1, t_player *pl2);

/*
** DISPLAY
*/

void				display_player_intro(t_player *player);
void				display_player_alive(t_vm *vm, t_player *player);
void				display_cycle(t_vm *vm);
void				display_resize(t_vm *vm);
void				display_move(t_vm *vm, t_process *proc);
void				display_ins(t_vm *vm, t_process *proc);
void				display_last_live(t_vm *vm, t_process *proc);
void				display_winner(t_vm *vm);
void				display_registers(t_vm *vm);
void				display(t_vm *vm, t_process *proc, int type);
void				display_proc_ins(t_vm *vm, t_process *proc);
void				set_colors(t_vm *vm);



void				display_ins_description(t_vm *vm, char *str, int opcode);
void				display_live_player(t_vm *vm, int op_code);
void				pl_death(t_vm *vm, t_process *proc);
void				pl_live(t_vm *vm, t_process *proc);
void				pl_victory(t_vm *vm, t_process *proc);
void				pl_cycle(t_vm *vm, t_process *proc);
void				pl_pc(t_vm *vm, t_process *proc);
void				lives_turn(t_vm *vm, t_process *proc);
void				cycles_to_autoresize(t_vm *vm, t_process *proc);
void				resize(t_vm *vm, t_process *proc);
void				cycle_end(t_vm *vm, t_process *proc);
void				move_one(t_vm *vm, t_process *proc);
void				cycle_nb(t_vm *vm, t_process *proc);
void				last_live(t_vm *vm, t_process *proc);
void				turn_player(t_vm *vm, t_process *proc);

/*
** ENV
*/

int					get_envar(char **env, char ****envvar);

/*
** INSTRUCTIONS
*/

void				getval_param_dest(t_vm *vm, t_process *proc,
												t_parameter *arg, int mod);
void				loadval(t_vm *vm, t_process *proc,
												t_parameter *arg, int val);
void				set_argval(t_parameter *arg, int index, int size);
int					no_ins(t_vm *vm, t_process *proc, t_parameter arg[3]);
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

/*
** PLAY
*/

int					play_one_cycle(t_vm *vm);
int					handle_end_cycle(t_vm *vm, int *cycle);
int					kill_process(t_vm *vm, t_list **proc_lst, t_list **proc);

/*
** UTILS
*/

int					mod(int val, int max);
int					ft_pow(int n, int pow);
int					getval(t_vm *vm, t_process *proc, t_parameter arg);
t_process			*get_proc_index(t_list *lst, int index);
int					is_reg(int num);
int					list_size(t_vm *vm, t_list *l);

/*
** TEMP delete at end
*/

void				display_arena(unsigned char *arena);
void				test_ins(t_vm *vm);
void				set_processes(t_vm *vm, t_process **proc);
void				test(t_vm vm);

/*
** process visual loop and events
*/

int					process_visu(t_vm *vm);

/*
** client connection to scorewar
*/

int					process_client(t_vm *vm);

#endif
