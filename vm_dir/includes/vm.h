/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 17:00:00 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "../../libop/includes/op.h"

# define TOT_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)
# define DEAD		-100

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
	int				nb_live;
	int				max_checks;
	int				win;
	int				nb_players;
	char			**files;
	int				dump;
	t_arena			arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS + 1];
}					t_vm;

typedef struct		s_arg
{
	int				val;
	int				nb_bytes;
}					t_arg;

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

void				error_exit(int n);
void				error_exit2(int n);
int					check_type(int ac, char **av);
void				init_vm(t_vm *vm, char **argv);
void				flags(t_vm *vm, int argc, char **argv);
void				read_files(t_vm *vm);
void				error_exit_mgc(char *name);
void				parse(t_vm *vm);

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
int				play(t_vm *vm, t_process **proc, t_op *tab);
int				launch_instruction(t_vm *vm, t_process *proc, t_op *tab);

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


#endif
