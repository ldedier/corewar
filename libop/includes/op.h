/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:01:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 18:43:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# include "libft.h"
# include "errors.h"

# define E_IND					2
# define E_REG					1
# define E_DIR					4

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define REGISTER_CHAR			'r'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789 "
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define NB_INSTRUCTIONS		16

# define LIVE_STR				"alive"
# define LD_STR					"load"
# define ST_STR					"store"
# define ADD_STR				"addition"
# define SUB_STR				"soustraction"
# define AND_STR				"et (and r1, r2, r3 r1&r2 -> r3"
# define OR_STR					"ou (or r1, r2, r3 r1 | r2 -> r3"
# define XOR_STR				"ou (xor r1, r2, r3 r1^r2 -> r3"
# define ZJMP_STR				"jump if zero"
# define LDI_STR				"load index"
# define STI_STR				"store index"
# define FORK_STR				"fork"
# define LLD_STR				"long load"
# define LLDI_STR				"long load index"
# define LFORK_STR				"long fork"
# define AFF_STR				"aff"

typedef char					t_arg_type;
typedef struct s_instruction	t_instruction;

typedef struct					s_op
{
	char						*instruction_name;
	char						nb_params;
	t_arg_type					arg_types[3];
	int							opcode;
	int							nb_cycles;
	char						*description;
	char						has_ocp;
	char						carry;
	char						describe_address;
}								t_op;

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_parameter
{
	t_arg_type					type;
	int							value;
	int							dest_value;
	char						*label_name;
	int							source_code_col;
	int							nb_bytes;
	char						retrieval_mode;
	t_instruction				*labeled_to;
}								t_parameter;

struct							s_instruction
{
	t_op						*op;
	t_parameter					params[3];
	unsigned int				address;
	int							nb_line;
	unsigned char				ocp;
	char						*source_code_line;
	char						*label;
	char						is_labeled;
};

enum							e_op
{
	NA, LIVE, LD, ST, ADD, SUB, AND, OR,
	XOR, ZJMP, LDI, STI, FORK, LLD, LLDI, LFORK, AFF
};

enum							e_nb_args
{
	ZERO, ONE, TWO, THREE
};

enum							e_has_ocp
{
	OCP_NO, OCP_YES
};

enum							e_mod_carry
{
	CARRY_NO, CARRY_YES
};

t_op							g_op_tab[NB_INSTRUCTIONS + 1];

int								get_bytelen(t_instruction *ins);
int								invalid_param(int type, int op);
int								getval_params(char *arena,
									t_instruction *ins, int i, int mod);
int								is_valid_ocp(unsigned char hex,
									t_instruction *ins);
int								getval_mod(char *arena, int index,
									int nb_bytes, int mod);
void							set_argval(t_parameter *arg,
									int index, int size);
int								get_ins(char *arena, t_instruction *ins,
									unsigned int i, int store);
int								read_ins(char *arena, t_instruction *ins,
									unsigned int *i, unsigned int mod);
int								store_arg(char *arena, t_instruction *ins,
									int i, int ocp);
void							set_optab(t_op **tab);
int								ft_encode_instructions(int fd,
									t_list *instructions, char create_label);
int								ft_parse_player_folder(char *folder_full_path,
									t_list **players_list);

#endif
