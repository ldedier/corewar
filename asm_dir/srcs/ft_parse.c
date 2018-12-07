/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:06:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/04 15:36:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_addco(char c, t_env *e)
{
	if (c == '\t')
	{
		e->parser.column_offset += TAB_SIZE -
			(e->parser.column_offset % TAB_SIZE);
	}
	else
		e->parser.column_offset++;
	return  (1);
}

int		ft_is_relevant(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isseparator(str[i]))
		i++;
	if (!str[i] || str[i] == COMMENT_CHAR || str[i] == ';')
		return (0);
	return (1);
}

void	ft_reset_parser(t_parser *parser, char *str)
{
	parser->nb_args_parsed = 0;
	parser->current_line = str;
	parser->column_offset = 0;
}

void		ft_init_parameter(t_parameter *parameter)
{
	parameter->type = 0;
	parameter->value = 0;
	parameter->source_code_col = 0;
	parameter->label_name = NULL;
}

int			ft_init_instruction(t_instruction *instruction, t_env *e)
{
	int i;

	instruction->address = e->champ.header.prog_size;
	instruction->nb_line = e->parser.nb_line;
	instruction->ocp = 0;
	i = 0;
	while (i < 3)
	{
		ft_init_parameter(&(instruction->params[i]));
		i++;
	}
	if (!(instruction->source_code_line = ft_strdup(e->parser.current_line)))
		return (1);
	return (0);
}

t_instruction	*ft_add_new_instruction(t_env *e)
{
	t_instruction	*instruction;
	if (!(instruction = (t_instruction *)malloc(sizeof(t_instruction))))
		return (NULL);
	if (ft_init_instruction(instruction, e))
	{
		free(instruction);
		return (NULL);
	}
	if (ft_add_to_list_ptr_back(&(e->champ.instructions), instruction,
				sizeof(t_instruction)))
	{
		free(instruction->source_code_line);
		free(instruction);
		return (NULL);
	}
	return (instruction);
}

int     ft_is_atouiable(char *s)
{
	long    res;
	int     start;
	int     i;

	res = 0;
	start = 0;
	while (ft_isseparator(s[start]))
		start++;
	i = start;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		if ((s[start] != '-' && (res * 10 + s[i] - '0' <= 4294967295))
				|| (s[start] == '-' && (res * 10 + s[i] - '0' <= 4294967296)))
			res = res * 10 + s[i] - '0';
		else
			return (0);
		i++;
	}
	return (1);
}

unsigned int	ft_patoui(char **str)
{
	int		multiplier;
	int		result;

	result = 0;
	multiplier = 1;
	if (**str == '-')
	{
		multiplier = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return ((unsigned int)(result * multiplier));
}

char			*ft_get_str(char **line)
{
	int         i;
	char        *str;

	str = *line;
	i = 0;
	while (str[i] && !ft_isseparator(str[i]))
		i++;
	str = ft_strndup(*line, i);
	(*line) += i;
	return (str);
}

int		ft_describe_label(char *str, int n, t_env *e)
{
	int i;

	i = 0;
	if (n == 0)
	{
		ft_log_error(LEXICAL_ERROR, 0, e);
		return (0);
	}
	while (str[i] && i < n)
	{
		if (!ft_is_in_str(LABEL_CHARS, str[i]))
		{
			ft_log_error(LEXICAL_ERROR, i, e);
			return (0);
		}
		i++;
	}
	return (1);
}


int		ft_process_populate_from_opcode(char *opcode_str, t_env *e)
{
	int i;

	i = 0;
	while (i < NB_INSTRUCTIONS)
	{
		if (!ft_strcmp(opcode_str, g_op_tab[i].instruction_name))
		{
			e->parser.current_instruction->op = g_op_tab[i];
			free(opcode_str);
			return (0);
		}
		i++;
	}
	free(opcode_str);
	return (1);
}

int		ft_log_custom_nb_params_error(int offset, t_env *e)
{
	char *str;
	char *nb_instructions;

	if (!(str = ft_strdup(e->parser.current_instruction->op.instruction_name)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, " instruction takes exactly ")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(nb_instructions =
				ft_itoa(e->parser.current_instruction->op.nb_params)))
	{
		free(str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (!(str = ft_strjoin_free(str, nb_instructions)))
	{
		free(nb_instructions);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(nb_instructions);
	if (!(str = ft_strjoin_free(str,
					e->parser.current_instruction->op.nb_params == 1 ?
					" argument !" : " arguments !")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	return (ft_log_error(str, offset, e));
}

int		ft_log_custom_wrong_param_type(char *arg_type, int index, int offset,
			t_env *e)
{
	char *str;
	char *index_str;

	if (!(str = ft_strdup(e->parser.current_instruction->op.instruction_name)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, "'s parameter #")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(index_str = ft_itoa(index + 1)))
	{
		free(str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (!(str = ft_strjoin_free(str, index_str)))
	{
		free(index_str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(index_str);
	if (!(str = ft_strjoin_free(str, " can not be of type ")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, arg_type)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	return (ft_log_error(str, offset, e));
}

int		ft_set_parser_co(int save, t_env *e, int ret)
{
	save = e->parser.column_offset;
	return (ret);
}
/*
int	ft_nb_words(char const *s)
{
	int res;
	int parseword;
	int i;

	res = 0;
	parseword = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isseparator(s[i]) && !parseword)
		{
			res++;
			parseword = 1;
		}
		else
		{
			if (ft_isseparator(s[i]) && parseword)
				parseword = 0;
		}
		i++;
	}
	return (res);
}
*/
int		ft_nb_params_coherent(char *str, t_env *e)
{
	int i;
	int nb_params;

	nb_params = 1;
	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == SEPARATOR_CHAR)
		{
			if (++nb_params > e->parser.current_instruction->op.nb_params)
			{
				ft_log_custom_nb_params_error(i, e);
				return (0);
			}
		}
	}
	if (nb_params == e->parser.current_instruction->op.nb_params)
		return (1);
	else
	{
		ft_log_custom_nb_params_error(i, e);
		return (0);
	}
}

int		ft_process_parse_register(char *str, int index, int offset, t_env *e)
{
	int ret;
	char *str2;
	int i;
	e->champ.header.prog_size += REG_SIZE;
	e->parser.current_instruction->params[index].nb_bytes = REG_SIZE;
	e->parser.current_instruction->ocp |= (REG_CODE << (6 - (2 * index)));
	i = 0;
	str2 = str;
	if (!(T_REG & e->parser.current_instruction->op.arg_types[index]))
		return (ft_log_custom_wrong_param_type("register", index, 0, e));
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	else if(!ft_is_atouiable(str))
		return (ft_log_error(LEXICAL_ERROR, offset + 1, e));
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	if (ret <= 0 || ret > REG_NUMBER)
		return (ft_log_error(INVALID_REG_NUMBER, offset, e));
	e->parser.current_instruction->params[index].type = T_REG;
	e->parser.current_instruction->params[index].value = ret;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int		ft_process_parse_label(char *str, int index, int offset, t_env *e)
{
	char *label_name;
	int i;

	if (!(label_name = ft_get_str(&str)))
		ft_log_error(MALLOC_ERROR, offset, e);
	e->parser.current_instruction->params[index].source_code_col = offset +
		e->parser.column_offset;
	e->parser.current_instruction->params[index].label_name = label_name;
	e->parser.current_instruction->params[index].type |= T_LAB;
	i = 0;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, ft_strlen(label_name) + offset, e));
	return (0);
}

int		ft_process_parse_indirect_value(char *str, int index, int offset, t_env *e)
{
	int ret;
	char *str2;
	int i;

	i = 0;
	str2 = str;
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	else if (!ft_is_atouiable(str))
		return (ft_log_error(LEXICAL_ERROR, offset + 1, e));
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	//if (ret < 0 || ret > REG_NUMBER)
	//	return (ft_log_error(INVALID_IND_NUMBER, offset + 1, e));
	e->parser.current_instruction->params[index].value = ret;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int		ft_process_parse_direct_value(char *str, int index, int offset, t_env *e)
{
	int ret;
	char *str2;
	int i;

	i = 0;
	str2 = str;
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	else if(!ft_is_atouiable(str))
		return (ft_log_error(LEXICAL_ERROR, offset + 1, e));
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	//	if (ret < 0 || ret > REG_NUMBER)
	//		return (ft_log_error(INVALID_IND_NUMBER, offset + 1, e));
	e->parser.current_instruction->params[index].value = ret;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int		ft_process_parse_indirect(char *str, int index, int offset, t_env *e)
{
	e->champ.header.prog_size += IND_SIZE;
	e->parser.current_instruction->params[index].nb_bytes = IND_SIZE;
	e->parser.current_instruction->ocp |= (IND_CODE << (6 - (2 * index)));
	if (!(T_IND & e->parser.current_instruction->op.arg_types[index]))
		return (ft_log_custom_wrong_param_type("indirect", index, 0, e));
	e->parser.current_instruction->params[index].type |= T_IND;
	if (str[0] == LABEL_CHAR)
		return (ft_process_parse_label(&(str[1]), index, offset + 1, e));
	else
		return (ft_process_parse_indirect_value(str, index, offset, e));
}

int		ft_process_parse_direct(char *str, int index, int offset, t_env *e)
{
	if (e->parser.current_instruction->op.describe_address)
	{
		e->parser.current_instruction->params[index].nb_bytes = IND_SIZE;
		e->champ.header.prog_size += IND_SIZE;
	}
	else
	{
		e->parser.current_instruction->params[index].nb_bytes = DIR_SIZE;
		e->champ.header.prog_size += DIR_SIZE;
	}
	e->parser.current_instruction->ocp |= (DIR_CODE << (6 - (2 * index)));
	if (!(T_DIR & e->parser.current_instruction->op.arg_types[index]))
		return (ft_log_custom_wrong_param_type("direct", index, 0, e));
	e->parser.current_instruction->params[index].type |= T_DIR;
	if (str[0] == LABEL_CHAR)
		return (ft_process_parse_label(&(str[1]), index, offset + 1, e));
	else
		return (ft_process_parse_direct_value(str, index, offset, e));
}

int		ft_process_parse_param(char *param, int index, int offset, t_env *e)
{
	(void)param;
	(void)index;
	(void)e;

	if (param[0] == REGISTER_CHAR)
		return (ft_process_parse_register(&(param[1]), index, 1, e));
	else if (ft_isdigit(param[0]) || param[0] == '-' || param[0] == LABEL_CHAR)
		return (ft_process_parse_indirect(param, index, 0, e));
	else if (param[0] == DIRECT_CHAR)
		return (ft_process_parse_direct(&(param[1]), index, 1, e));
	else
		return ft_log_error(LEXICAL_ERROR, offset, e);
	return (0);
}

int		ft_parse_param(char *str, int index, t_env *e)
{
	int i;
	int ret;

	i = 0;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	ret = ft_process_parse_param(&(str[i]), index, i, e);
	if (e->champ.header.prog_size > CHAMP_MAX_SIZE)
		return (ft_log_error(TOO_BIG_CHAMP, 0, e));
	return (ret);
}

void	ft_update_co(char *str, t_env *e)
{
	int i;

	i = 0;
	while (str[i] && ft_addco(str[i], e))
		i++;
}

int		ft_process_parse_params(char **params_split,
		t_env *e)
{
	int i;
	int save;

	i = 0;
	while (params_split[i])
	{
		save = e->parser.column_offset;
		if (ft_parse_param(params_split[i], i, e))
		{
			ft_free_split(params_split);
			return (1);
		}
		e->parser.column_offset = save;
		ft_update_co(params_split[i], e);
		e->parser.column_offset++;
		i++;
	}
	ft_free_split(params_split);
	return (0);
}

int		ft_parse_params(char *str, int i, t_env *e)
{
	char **params_split;
	int start;
	int save;

	save = e->parser.column_offset;
	start = i;
	while (str[start] && ft_isseparator(str[start]) && ft_addco(str[start], e))
		start++;
	if (!str[start])
	{
		e->parser.column_offset = save;
		return (ft_log_error(NO_PARAMETERS, -
					ft_strlen(e->parser.current_instruction->op.instruction_name), e));
	}
	if (!(params_split = ft_strsplit(&(str[start]), SEPARATOR_CHAR)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(ft_nb_params_coherent(&(str[start]), e)))
		return (1);
	return (ft_process_parse_params(params_split, e));
}

int		ft_populate_from_opcode(char *str, int start, int i, t_env *e)
{
	char *opcode_str;

	if (!(opcode_str = ft_strndup(&(str[start]), i - start)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (ft_process_populate_from_opcode(opcode_str, e))
		return (ft_log_error(UNKNOWN_INSTRUCTION, 0, e));
	e->champ.header.prog_size++;
	if (e->parser.current_instruction->op.has_ocp)
		e->champ.header.prog_size++;
	e->parser.column_offset += i - start;
	return (ft_parse_params(str, i, e));
}

int		ft_parse_opcode(char *str, int start, t_env *e)
{
	int i;

	while (ft_isseparator(str[start]) && ft_addco(str[start], e))
		start++;
	i = start;
	while (!ft_isseparator(str[i]) && str[i])
		i++;
	return (ft_populate_from_opcode(str, start, i, e));
}

t_label		*ft_new_label(char *name, int address)
{
	t_label	*label;

	if (!(label = (t_label *)(malloc(sizeof(t_label)))))
		return (NULL);
	label->name = name;
	label->address = address;
	return (label);
}

t_label	*ft_get_label(t_list *labels, char *label_name)
{
	t_list *ptr;
	t_label *label;

	ptr = labels;
	while (ptr != NULL)
	{
		label = (t_label *)(ptr->content);
		if (!ft_strcmp(label->name, label_name))
			return (label);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_add_new_label(char *str, int length, t_env *e)
{
	t_label	*label;
	char	*label_name;

	if (!(label_name = ft_strndup(str, length)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (ft_get_label(e->champ.labels, label_name))
	{
		free(label_name);
		return (ft_log_error(EXISTS_LABEL, 0, e));
	}
	if (!(label = ft_new_label(label_name, e->champ.header.prog_size)))
	{
		free(label_name);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (ft_add_to_list_ptr_back(&(e->champ.labels), label, sizeof(t_label)))
	{
		ft_free_label(label);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	e->parser.column_offset += length + 1;
	return (0);
}

int		ft_parse_instruction(char *str, t_env *e)
{
	int start;
	int i;

	start = 0;
	while (ft_isseparator(str[start]) && ft_addco(str[start], e))
		start++;
	i = start;
	while (str[i] && !ft_isseparator(str[i]) && str[i] != LABEL_CHAR)
		i++;
	if (!str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	else if (str[i] == LABEL_CHAR)
	{
		if (ft_describe_label(&(str[start]), i - start, e))
		{
			if (ft_add_new_label(&(str[start]), i - start, e))
				return (1);
			return (ft_parse_opcode(str, i + 1, e));
		}
		else
			return (1);
	}
	else
		return (ft_populate_from_opcode(str, start, i, e));
	return (0);
}

int		ft_is_only_label(char *str)
{
	int start;
	int i;

	start = 0;
	while (ft_isseparator(str[start]))
		start++;
	i = start;
	while (str[i] && ft_is_in_str(LABEL_CHARS, str[i]))
		i++;
	if (!str[i])
		return (0);
	else if (str[i] == LABEL_CHAR)
	{
		i++;
		while (str[i])
		{
			if (!(ft_isseparator(str[i])))
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int		ft_parse_label(char *str, t_env *e)
{
	int start;
	int i;

	start = 0;
	while (ft_isseparator(str[start]) && ft_addco(str[start], e))
		start++;
	i = start;
	while (str[i] && ft_is_in_str(LABEL_CHARS, str[i]))
		i++;
	if (ft_add_new_label(&(str[start]), i - start, e))
		return (1);
	else
		return (0);
}

int		ft_parse_line_source_code(char *str, t_env *e)
{
	ft_reset_parser(&(e->parser), str);
	if (ft_is_only_label(str))
		return (ft_parse_label(str, e));
	else
	{
		if (!(e->parser.current_instruction = ft_add_new_instruction(e)))
			return (ft_log_error(MALLOC_ERROR, 0, e));
		if (ft_parse_instruction(str, e))
			return (1);
	}
	return (0);
}

char	*ft_refine_line(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != COMMENT_CHAR && str[i] != ';')
		i++;
	return (ft_strndup(str, i));
}

int		ft_parse_line(char *str, t_env *e, int fd)
{
	char *refined;
	int ret;

	if (!(refined = ft_refine_line(str)))
		return (ft_log_error_no_line(MALLOC_ERROR, e));
	if (!e->parser.parsed_comment || !e->parser.parsed_name)
	{
		ft_reset_parser(&(e->parser), str);
		ret = ft_parse_line_header(refined, e, 0, fd);
		free(refined);
	}
	else
	{
		ret = (ft_parse_line_source_code(refined, e));
		free(refined);
	}
	return (ret);
}

int		ft_process_fill_instruction_label_value(t_instruction *instruction,
		int index, t_list *labels)
{
	t_list	*ptr;
	t_label	*label;

	ptr = labels;
	while (ptr != NULL)
	{
		label = (t_label *)ptr->content;
		if (!ft_strcmp(instruction->params[index].label_name, label->name))
		{
			if (instruction->params[index].type & T_DIR)
				instruction->params[index].value =
					label->address - instruction->address;
			else
				instruction->params[index].value =
					label->address - instruction->address;
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

int		ft_fill_instructions_labels_values(t_env *e)
{
	t_list			*ptr;
	t_instruction	*instruction;
	int				i;

	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instruction = (t_instruction *)(ptr->content);
		i = 0;
		while (i < instruction->op.nb_params)
		{
			if (instruction->params[i].type & T_LAB)
			{
				if (ft_process_fill_instruction_label_value(instruction,
							i, e->champ.labels))
					return (ft_log_no_label_error(instruction,
								i, e));
			}
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}

int		ft_parse_asm(char *str, t_env *e)
{
	char *line;
	int ret;

	if ((e->parser.fd = open(str , O_RDONLY)) == -1)
	{
		perror(str);
		return (1);
	}
	else if ((ret = ft_switch_extension(str, ".s", ".cor", &(e->champ.cor_name))))
	{
		if (ret == -1)
			return ft_log_error_no_line(MALLOC_ERROR, e);
		else
			return ft_log_error_no_line("File must be of extension \'.s\'", e);
	}
	while (get_next_line(e->parser.fd, &line))
	{
		e->parser.nb_line++;
		if (ft_is_relevant(line)) // pas une ligne vide ou un commentaire
		{
			if (ft_parse_line(line, e, e->parser.fd) == 1)
			{
				ft_lstdel_value(&(e->champ.instructions));
				return (1);
			}
		}
		free(line);
	}
	if (ft_fill_instructions_labels_values(e))
		ft_printf(":(\n");
	else
	{
		ft_print_instructions(e->champ.instructions);
		ft_print_labels(e->champ.labels);
		ft_printf(":)\n");
	}
	free(line);
	close(e->parser.fd);
	return (0);
}
