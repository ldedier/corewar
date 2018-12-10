/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:01:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 19:00:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
 ** Toutes les tailles sont en octets.
 ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 */
# include "libft.h"

# include "color.h"

# define REG_SIZE				1
# define DIR_SIZE				4
# define IND_SIZE				2

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
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
# define CYCLE_TO_DIE			100 //anciennement 1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				2 //anciennement 10


# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define NB_INSTRUCTIONS		16

# define LIVE_STR			"alive"
# define LD_STR				"load"
# define ST_STR				"store"
# define ADD_STR			"addition"
# define SUB_STR			"soustraction"
# define AND_STR			"et (and r1, r2, r3 r1&r2 -> r3"
# define OR_STR				"ou (or r1, r2, r3 r1 | r2 -> r3"
# define XOR_STR			"ou (xor r1, r2, r3 r1^r2 -> r3"
# define ZJMP_STR			"jump if zero"
# define LDI_STR			"load index"
# define STI_STR			"store index"
# define FORK_STR			"fork"
# define LLD_STR			"long load"
# define LLDI_STR			"long load index"
# define LFORK_STR			"long fork"
# define AFF_STR			"aff"

# define 1_R				REG_SIZE
# define 1_D				DIR_SIZE
# define 1_I				IND_SIZE
# define 2_RD				1_R + 1_D
# define 2_RI				1_R + 1_I
# define 2_DI				1_D + 1_I
# define 3_RDI				2_RD + 1_I
# define ARG3_BYTES			8
# define ARG1_BYTES			3 * ARG
# define ARG2_BYTES			2 * ARG
# define GETARG(A1, A2, A3)		(A1 << ARG1_BYTES) | (A2 << ARG2_BYTES) | (A3 << ARG3_BYTES)	
# define LIVE_ARG_TYPE			GET_ARGTYPE(1_D, 0, 0)
# define LD_ARG_TYPE			GET_ARGTYPE(2_DI, 1_D, 0) 
# define ST_ARG_TYPE			GET_ARGTYPE(1_R, 2_RI, 0)
# define ADD_ARG_TYPE			GET_ARGTYPE(1_R, 1_R, 1_R)
# define SUB_ARG_TYPE			GET_ARGTYPE(1_R, 1_R, 1_R)
# define OR_ARG_TYPE			GET_ARGTYPE(3_RDI, 3_RDI, 1_R)
# define AND_ARG_TYPE			GET_ARGTYPE(3_RDI, 3_RDI, 1_R)
# define XOR_ARG_TYPE			GET_ARGTYPE(3_RD, 3_RD, 1_R)
# define ZJMP_ARG_TYPE			GET_ARGTYPE(1_D, 0, 0)
# define LDI_ARG_TYPE			GET_ARGTYPE(3_RDI, 2_RDi, 1_R)
# define STI_ARG_TYPE			GET_ARGTYPE(1_R, 3_RDI, 2_RD)
# define FORK_ARG_TYPE			GET_ARGTYPE(1_D, 0, 0)
# define LLD_ARG_TYPE			GET_ARGTYPE(2_DI, 1_R, 0)
# define LLDI_ARG_TYPE			GET_ARGTYPE(3_RDI, 2_RD, 1_R)
# define LFORK_ARG_TYPE			GET_ARGTYPE(1_D, 0)
# define AFF_ARG_TYPE			GET_ARGTYPE(1_R, 0)

# define NEEDS_OCP				60925



typedef char	t_arg_type;

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

typedef struct		s_parameter
{
	t_arg_type		type; //T_REG || T_IND || T_DIR || T_LAB
	int				value;
	char			*ptr;
	char			*label_name;
	int				source_code_col;
	int				nb_bytes;
}					t_parameter;

typedef struct		s_instruction
{
	t_op			op;
	t_parameter		params[3];
	unsigned int	address;
	int				nb_line;
	unsigned char	ocp;
	char			*source_code_line;
}					t_instruction;

enum				e_op
{
	NA, LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP, LDI, STI, FORK, LLD, LLDI, LFORK, AFF
};

enum				e_nb_args
{
	ZERO, ONE, TWO, THREE
};

enum				e_has_ocp
{
	OCP_NO, OCP_YES
};

enum				e_mod_carry
{
	CARRY_NO, CARRY_YES
}

t_op							g_op_tab[NB_INSTRUCTIONS + 1];




int								get_instruction(char *arena, t_instruction *ins, int i, int mod);
int								store_arg(char *arena, t_instruction *ins, int i, int ocp);
void							set_optab(t_op **tab);
int								ft_encode_instructions(int fd, t_list *instructions);

#endif
