/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:49:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 20:23:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

typedef struct	s_label
{
	char		*name;
	int			address;
}				t_label;

typedef struct	s_parameter
{
	t_arg_type	parameter_type; //T_REG || T_DIR || T_IND || T_LAB
	int			value;
	char		*label_name;
}				t_parameter;

typedef struct	s_instruction
{
	t_parameter	params[3];
	char		opcode;
	int			address;
	int			nb_line;
	char		nb_params;
}				t_instruction;

typedef struct	s_champion
{
	t_list		*labels;
	char		*file_name;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	t_list		*instructions;
}				t_champion;

typedef struct	s_parser
{
	int			nb_line;
	char		parsed_name;
	char		parsed_comment;
}				t_parser;

typedef struct	s_env
{
	t_champion	champ;
	t_parser	parser;
}				t_env;

/*
** parse le file filename: print l'erreur et retourne 1, retourne 0 sinon
** (mets a jour le champion)
*/

int				ft_parse_asm(char *filename, t_env *e);
int				ft_parse_line_header(char *str, t_env *e);
int				ft_parse_line_source_code(char *str, t_env *e);
char			**read_file(char **argv);
int 			read_name_file(char *argv, t_env *env);
/*
** encode le
*/
int				ft_encode_to_cor(char *file, t_env *e);

#endif
