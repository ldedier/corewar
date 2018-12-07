/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:01:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 21:53:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
 ** Toutes les tailles sont en octets.
 ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 */

# define REG_SIZE				1
# define IND_SIZE				2
# define DIR_SIZE				4

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
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define NB_INSTRUCTIONS		16

typedef struct					s_op
{
	char						*instruction_name;
	char						nb_params;
	t_arg_type					arg_types[3];
	int							opcode;
	int							nb_cycles;
	char						*description;
	char						has_ocp;
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
	t_arg_type		type; //T_REG || T_DIR || T_IND || T_LAB
	int				value;
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
	LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP, LDI, STI, FORK, LLD, LLDI, LFORK, AFF
};


t_op							g_op_tab[NB_INSTRUCTIONS + 1];




int								get_instruction(char *arena, t_instruction *ins, int i, int mod);
int								store_arg(char *arena, t_instruction *ins, int i, int ocp);
void							set_optab(t_op **tab);

#endif
