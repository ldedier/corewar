/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:49:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 23:38:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "libft.h"
# include "op.h"

# define MAX_ERRORS_DISPLAYED 20

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
	t_list		*instructions;
	t_list		*labels;
	char		*file_name;
	char		*assembly_name;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
}				t_champion;

typedef struct	s_parser
{
	int			nb_line;
	char		parsed_name;
	char		parsed_comment;
	int			nb_errors;
	int			nb_warnings;
	char		too_much_errors_displayed;
}				t_parser;

typedef struct	s_env
{
	t_champion	champ;
	t_parser	parser;
}				t_env;

/*
** parse the filenamefile : print the error and return 1, else return 0
** updates the champion (especially its instructions list)
*/

int				ft_parse_asm(char *filename, t_env *e);

int				ft_parse_line_header(char *str, t_env *e);
int				ft_parse_line_source_code(char *str, t_env *e);
char			**read_file(char **argv);
int 			read_name_file(char *argv, t_env *env);

/*
** encode the .cor file with the instructions list
*/

int				ft_encode_to_cor(char *file, t_env *e);

int				ft_log_error(char *error, char *line, int column, t_env *e);
int				ft_log_error_no_line(char *str, t_env *e);
int				ft_log_warning(char *str, char *line, int column, t_env *e);
int				ft_log_warning_no_line(char *str, t_env *e);
void			ft_print_logs_stats(t_env *e);
#endif
