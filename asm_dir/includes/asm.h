/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:49:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/15 01:42:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "libft.h"
# include "op.h"
# include "champion.h"

# define MAX_ERRORS_DISPLAYED	20
# define TAB_SIZE				8
# define MALLOC_ERROR			"could not execute malloc instruction"
# define LEXICAL_ERROR			"lexical error"
# define EXCESSIVE_VALUE		"excessive value: expect overflow"
# define UNKNOWN_INSTRUCTION	"unknown instruction"
# define EXISTS_LABEL			"label name already defined"
# define NO_PARAMETERS			"no parameter given for this instruction"
# define INVALID_REG_NUMBER		"invalid register number: max = "
# define ZERO_SEPARATOR			"syntax error: NULL character found"
# define EOF_SEPARATOR			"syntax error: unexpected end of input"

typedef struct		s_parser
{
	t_instruction	*current_instruction;
	int				nb_args_parsed;
	int				nb_line;
	char			parsed_name;
	char			parsed_comment;
	int				parsed_chars;
	char			parsing_name;
	char			parsing_comment;
	int				nb_errors;
	int				nb_warnings;
	char			*current_line;
	int				column_offset;
	int				fd;
	char			parse_param;
	char			nb_params;
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
void				ft_init_parser(t_parser *parser);
void				ft_init_env(t_env *e, char *filename);
int					check_comment(char *str, t_env *env);
int					ft_parse_asm(char *filename, t_env *e);
int					ft_parse_line_header(char *str, t_env *env);
int					ft_parse_line_source_code(char *str, t_env *e);
char				**read_file(char **argv);
int					read_name_file(char *argv, t_env *env);
char				*ft_refine_line(char *str, t_env *e);
int					ft_parse_line_source_code(char *str, t_env *e);
int					ft_parse_label(char *str, t_env *e);
int					ft_is_only_label(char *str);
int					ft_add_new_label(char *str, int length, t_env *e);
int					ft_parse_instruction(char *str, t_env *e, int start);
t_label				*ft_get_label(t_list *labels, char *label_name);
t_label				*ft_new_label(char *name, int address);
int					ft_parse_opcode(char *str, int start, t_env *e);
int					ft_populate_from_opcode(char *str, int start, int i,
						t_env *e);
int					ft_parse_params(char *str, int i, t_env *e);
int					ft_process_parse_params(char **params_split, t_env *e);
void				ft_update_co(char *str, t_env *e);
int					ft_parse_param(char *str, int index, t_env *e);
int					ft_process_parse_param(char *param, int index, t_env *e);
int					ft_process_parse_direct(char *str, int index, t_env *e);
int					ft_process_parse_indirect(char *str, int index, t_env *e);
int					ft_process_parse_dir_value(char *str, int index, int offset,
						t_env *e);
int					ft_process_parse_ind_value(char *str, int index, int offset,
						t_env *e);
int					ft_process_parse_label(char *str, int index, int offset,
						t_env *e);
int					ft_nb_params_coherent(char *str, t_env *e);
int					ft_process_parse_register(char *str, int index, t_env *e);
int					ft_log_custom_wrong_param_type(char *arg_type, int index,
						int offset, t_env *e);
int					ft_log_custom_nb_params_error(t_env *e);
int					ft_process_populate_from_opcode(char *opcode_str, t_env *e);
int					ft_describe_label(char *str, int n, t_env *e);
char				*ft_get_str(char **line);
unsigned int		ft_patoui(char **str);
int					ft_is_atoiable(char *s);
t_instruction		*ft_add_new_instruction(t_env *e);
int					ft_init_instruction(t_instruction *instruction, t_env *e);
void				ft_init_parameter(t_parameter *parameter);
void				ft_reset_parser(t_parser *parser, char *str);
int					ft_is_relevant(char *str, t_env *e);
int					ft_addco(char c, t_env *e);
int					ft_fill_instructions_labels_values(t_env *e);
int					ft_process_fill_instruction_label_value
					(t_instruction *instru, int index, t_list *labels);
int					ft_process_nb_params_coherent(int *save, t_env *e, char c);
int					check_after_comment(char *tmp, int i, t_env *env);
void				check_comment_exist(t_env *env, int j);
void				get_comment_other_line_suite(t_env *env, int i);
int					get_comment_other_line(t_env *env, int fd, int i);
int					read_comment_continue(char *line, int i, t_env *env,
					int fd);
/*
** encode the .cor file with the instructions list
*/
void				ft_add_padding(int fd, int total_bytes);
int					ft_encode_to_cor(char *file, t_env *e);
int					ft_write(int fd, int value, int size);
void				ft_init_env(t_env *e, char *filename);
int					ft_log_error(char *error, int column, t_env *e);
int					ft_log_error_no_line(char *str, t_env *e);
int					ft_log_warning(char *str, int column, t_env *e);
int					ft_log_warning_no_line(char *str, t_env *e);
int					ft_log_no_label_error(t_instruction *ins, int index,
						t_env *e);
void				ft_print_param(t_parameter param, int index);
void				ft_print_instruction(t_instruction *ins);
void				ft_print_instructions(t_list *instructions);
void				ft_print_label(t_label *label);
void				ft_print_labels(t_list *labels);
void				ft_print_logs_stats(t_env *e);
void				ft_free_label(t_label *label);
void				ft_free_all(t_env *e);
int					process_fill_buffer(char *str, int buffer_len,
						char *buffer, t_env *e);
int					ft_process_parse_comment(char *str, t_env *e);
int					ft_process_parse_name(char *str, t_env *e);
void				end_parse(t_env *e);
int					is_comment(char c);
int					ft_log_custom_invalid_reg_number(int offset, t_env *e);
int					ft_log_error_too_long_parsing(int offset, t_env *e);
#endif
