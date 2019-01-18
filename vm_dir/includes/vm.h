/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/18 19:47:16 by uboumedj         ###   ########.fr       */
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
	void			*dest;
	int				dest_index;
	int				value;
	int				pc;
	int				cycles;
}					t_pending;

typedef struct		s_process
{
	t_player		*player;
	t_pending		pending;
	int				live;
	unsigned int	reg[REG_NUMBER];
	int				pc;
	int				ins_bytelen;
	int				cycle;
	int				ins_cycle;
	unsigned char	carry;
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

typedef struct		s_vm
{
	int				c_to_die;
	int				checks;
	int				win;
	int				cycle;
	int				total_cycle;
	int				nb_players;
	long long int	nb;
	char			**files;
	int				dump;
	char			color[MAX_PL_COLOR];
	t_client		client;
	t_visu			visu;
	char			arena[MEM_SIZE];
	t_metadata		metarena[MEM_SIZE];
	t_player		player[MAX_PLAYERS];
	t_player		local_player[MAX_PLAYERS];
	t_list			*proc;
	t_list			*killed_proc;
	t_list			*live_ok;
	int				live;
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

void				ft_error_exit(const char *error);
void				error_exit_msg(const char *error);
int					check_type(int ac, char **av);
void				check_header(void);
void				init_vm(t_vm *vm, char **argv, char **env);
void				corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
void				flags(t_vm *vm, int argc, char **argv);
int					read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);
void				dispatch_players(t_vm *vm, t_player *player);
void				dispatch_players_init(t_vm *vm);
int					init_processes(t_vm *vm);
void				init_local_players(t_vm *vm);
void				update_nb_players(t_vm *vm);
int					ft_get_potential_num(int player_num);
void				ft_set_numbers(t_player players[MAX_PLAYERS],
															t_player *player);
void				update_buttons(t_vm *vm);

/*
** DISPLAY
*/

void				display_ins_description(t_vm *vm, char *str, int opcode);
void				display_live_player(t_vm *vm, int op_code);
void				display_registers(t_vm *vm);
void				display(t_vm *vm, t_process *proc, int type);
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

void				process_cycle(t_vm *vm);
int					handle_end_cycle(t_vm *vm, int *cycle);
int					play(t_vm *vm);

/*
** UTILS
*/

int					mod(int val, int max);
int					ft_pow(int n, int pow);
int					getval(t_vm *vm, t_process *proc, t_parameter arg);
t_process			*get_proc_index(t_list *lst, int index);
t_player			*get_player_num(t_list *lst, int num);
int					is_reg(int num);

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
