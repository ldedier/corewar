/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/13 22:43:46 by ldedier          ###   ########.fr       */
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

# define NEEDS_OCP	60925
# define NB_TYPES	3

typedef struct		s_process
{
	int				id;
	char			colindex;
	char			name[PROG_NAME_LENGTH + 1];
	int				live;
	unsigned char	reg[REG_NUMBER];
	int				pc;
	int				ins_cycle;
	int				cycle;
	unsigned char	carry;
}					t_process;

typedef struct		s_metadata
{
	char			color_index;
}					t_metadata;

typedef struct		s_live
{
	int		nb;
	int		total_pl;
	int		last_pl;
}									t_live;

typedef struct		s_vm
{
	int				c_to_die;
	int				checks;
	int				win;
	int				cycle;
	int				nb_players;
	char			**files;
	int				dump;
	char			color[MAX_PL_COL];
	t_client		client;
	t_visu			visu;
	char			arena[MEM_SIZE];
	t_metadata		metarena[MEM_SIZE];
	t_player		player[MAX_PLAYERS];
	t_player		local_player[MAX_PLAYERS];
	t_list			*proc;
	t_live			 live;
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
void				init_vm(t_vm *vm, char **argv);
void				corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
void				flags(t_vm *vm, int argc, char **argv);
int					read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);
int					dispatch_players(t_vm *vm);

/*
** DISPLAY
*/

void				display(t_vm *vm, t_process *proc, int type);
void				pl_death(t_vm *vm, t_process *proc);
void				pl_live(t_vm *vm, t_process *proc);
void				pl_victory(t_vm *vm, t_process *proc);
void				pl_cycle(t_vm *vm, t_process *proc);
void				pl_pc(t_vm * vm, t_process *proc);
void				lives_turn(t_vm *vm, t_process *proc);
void				cycles_to_autoresize(t_vm *vm, t_process *proc);
void				resize(t_vm *vm, t_process *proc);
void				cycle_end(t_vm *vm, t_process *proc);
void				move_one(t_vm *vm, t_process *proc);
void				cycle_nb(t_vm *vm, t_process *proc);
void				last_live(t_vm *vm, t_process *proc);
void				turn_player(t_vm *vm, t_process *proc);


/*
** INSTRUCTIONS
*/

int					getval(t_vm *vm, t_process *proc, t_parameter arg);
void				loadval(t_vm *vm, t_process *proc, t_parameter arg, int val);
void				set_argval(t_parameter *arg, int index, int size);
int					check_reg(int r);

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

//void				check_resize_cycle(t_vm *vm, int *cycle);
int					play(t_vm *vm);
//void				launch_instruction(t_vm *vm, int player);

/*
** UTILS
*/

int					mod(int val, int max);
int					ft_pow(int n, int pow); // remove?
t_process		*get_proc_index(t_list *lst, int index);
t_process		*get_proc_num(t_list *lst, int num);

// TEMP delete at end

void				display_arena(unsigned char *arena); //tmp for test and debug
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
