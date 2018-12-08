/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 21:56:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include "champion.h"
# include "player.h"
# include "visu.h"
# include "client.h"
# include "errors.h"
# include <fcntl.h>
# define DEAD		-100

typedef struct		s_arena
{
	char			hex;
}					t_arena;

typedef struct		s_vm
{
	int				c_to_die;
	int				nb_live;
	int				max_checks;
	int				win;
	int				nb_players;
	char			**files;
	int				dump;
	t_client		client;
	t_visu			visu;
	t_arena			arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS + 1];
}					t_vm;

typedef struct		s_process
{
	int				id;
	int				live;
	unsigned char	reg[REG_NUMBER];
	int				pc;
	int				cycle;
	unsigned char	carry;
}					t_process;

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
void				error_exit_msg(const char *error);
int					check_type(int ac, char **av);
void				init_vm(t_vm *vm, char **argv);
void				corehub_port_and_address(t_vm *vm, int argc,
						char **argv, int *cur);
void				flags(t_vm *vm, int argc, char **argv);
int					read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);
void				dispatch_players(t_vm *vm, t_process **process);

/*
** INSTRUCTIONS
*/

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

int				check_resize_cycle(t_vm *vm, int *cycle);
int				play(t_vm *vm, t_process **proc);
int				launch_instruction(t_vm *vm, t_process *proc);

/*
** ENV
*/

//void				set_optab(t_op	**tab);

/*
** UTILS
*/

int					mod(int val, int max);
int					ft_pow(int n, int pow);

// TEMP delete at end
void				display_arena(t_arena *arena); //tmp for test and debug
void				test_ins(t_vm *vm);
void				set_processes(t_vm *vm, t_process **proc);

/*
** process visual loop and events
*/
int					process_visu(t_vm *vm);

/*
** client connection to scorewar
*/
int					process_client(t_vm *vm);
#endif
