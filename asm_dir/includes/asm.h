/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:49:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/01 17:56:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "libft.h"
# include "op.h"

# define MAX_ERRORS_DISPLAYED	20
# define MALLOC_ERROR			"could not execute malloc instruction"
# define LEXICAL_ERROR			"lexical error"

typedef struct		s_label
{
	char			*name;
	int				address;
}					t_label;

typedef struct		s_parameter
{
	t_arg_type		type; //T_REG || T_DIR || T_IND || T_LAB
	int				value;
	char			*label_name;
}					t_parameter;

typedef struct		s_instruction
{
	t_parameter		params[3];
	unsigned char	opcode;
	unsigned int	address;
	int				nb_line;
	char			nb_params;
	unsigned char	ocp;
}					t_instruction;

typedef struct		s_champion
{
	t_header		header;
	t_list			*instructions;
	t_list			*labels;
	char			*file_name;
	char			*assembly_name;
}					t_champion;

typedef enum		e_parse_phase
{
	OPCODE,
	ARG_TYPE_RESEARCH,
	ARG
}					t_parse_phase;

typedef struct		s_parser
{
	t_instruction	*current_instruction;
	t_parse_phase	phase;
	int				nb_args_parsed;
	int				nb_line;
	char			parsed_name;
	char			parsed_comment;
	int				nb_errors;
	int				nb_warnings;
	char			*current_line;
	int				column_offset;
	char			too_much_errors_displayed;
}					t_parser;

typedef struct		s_env
{
	t_champion		champ;
	t_parser		parser;
}					t_env;

/*
** parse the filenamefile : print the error and return 1, else return 0
** updates the champion (especially its instructions list)
*/

int					ft_parse_asm(char *filename, t_env *e);

int					ft_parse_line_header(char *str, t_env *e);
int					ft_parse_line_source_code(char *str, t_env *e);
char				**read_file(char **argv);
int					read_name_file(char *argv, t_env *env);

/*
** encode the .cor file with the instructions list
*/

int					ft_encode_to_cor(char *file, t_env *e);

void				ft_init_env(t_env *e, char *filename);
int					ft_log_error(char *error, int column, t_env *e);
int					ft_log_error_no_line(char *str, t_env *e);
int					ft_log_warning(char *str, int column, t_env *e);
int					ft_log_warning_no_line(char *str, t_env *e);

void				ft_print_param(t_parameter param);
void				ft_print_instruction(t_instruction *instruction);
void				ft_print_instructions(t_list *instructions);
void				ft_print_logs_stats(t_env *e);
#endif
