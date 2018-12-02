/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:06:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/01 17:57:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_is_relevant(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isseparator(str[i]))
		i++;
	if (!str[i] || str[i] == COMMENT_CHAR)
		return (0);
	return (1);
}

void	ft_reset_parser(t_parser *parser, char *str)
{
	parser->phase = OPCODE;
	parser->nb_args_parsed = 0;
	parser->current_line = str;
	parser->column_offset = 0;
}

t_instruction		*ft_append_new_instruction(t_env *e)
{
	t_instruction	*instruction;
	if (!(instruction = (t_instruction *)malloc(sizeof(t_instruction))))
		return (NULL);
	instruction->address = e->champ.header.prog_size;
	instruction->nb_line = e->parser.nb_line;
	instruction->nb_params = -1;
	instruction->opcode = -1;
	if (ft_add_to_list_ptr_back(&(e->champ.instructions), instruction,
		sizeof(t_instruction)))
	{
		free(instruction);
		return (NULL);
	}
	return (instruction);
}


int		ft_describe_label(char *str, int n, t_env *e, int log)
{
	int i;

	i = 0;
	if (n == 0)
	{
		if (log)
			ft_log_error(LEXICAL_ERROR, 0, e);
		return (0);
	}
	while (str[i] && i < n)
	{
		if (!ft_is_in_str(LABEL_CHARS, str[i]))
		{
			if (log)
				ft_log_error(LEXICAL_ERROR, i, e);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_appco(char c, t_env *e)
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

int		ft_populate_opcode(char *str, int start, int i, t_env *e)
{
	(void)e;
	char *str2 = ft_strndup(&(str[start]), i - start);
	ft_printf("opcode parsed: %s\n", str2);
	return (0);
}

int		ft_parse_opcode(char *str, int start, t_env *e)
{
	int i;

	while (ft_isseparator(str[start]) && ft_appco(str[start], e))
		start++;
	i = start;
	while (!ft_isseparator(str[i]) && str[i])
		i++;
	return ft_populate_opcode(str, start, i, e);
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

int		ft_add_new_label(char *str, int length, t_env *e)
{
	t_label	*label;
	char	*label_name;

	if (!(label_name = ft_strndup(str, length)))
		return (1);
	if (!(label = ft_new_label(label_name, e->champ.header.prog_size)))
		return (1);
	if (ft_add_to_list_ptr_back(&(e->champ.labels), label, sizeof(t_label)))
		return (1);
	return (0);
}

int		ft_parse_label_and_opcode(char *str, t_env *e)
{
	int start;
	int i;

	start = 0;
	while (ft_isseparator(str[start]) && ft_appco(str[start], e))
		start++;
	i = start;
	while (str[i] && !ft_isseparator(str[i]) && str[i] != LABEL_CHAR)
		i++;
	if (!str[i])
		return (ft_log_error(LEXICAL_ERROR, i, e));
	else if (str[i] == LABEL_CHAR)
	{
		if (ft_describe_label(&(str[start]), i - start, e, 1))
		{
			if (ft_add_new_label(&(str[start]), i - start, e))
				return (ft_log_error(MALLOC_ERROR, 0, e));
			return (ft_parse_opcode(str, i + 1, e));
		}
		else
			return (1);
	}
	else
	{
		return (ft_populate_opcode(str, start, i, e));
	}
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

int		ft_parse_line_source_code(char *str, t_env *e)
{
	ft_reset_parser(&(e->parser), str);
	if (ft_is_only_label(str))
	{

	}
	else
	{
		if (!(e->parser.current_instruction = ft_append_new_instruction(e)))
			return (ft_log_error(MALLOC_ERROR, 0, e));
		if (ft_parse_label_and_opcode(str, e))
			return (1);
	}
//	ft_printf("%s\n", str);
	return (0);
}

int		ft_parse_line(char *str, t_env *e)
{
	if ((!e->parser.parsed_comment || !e->parser.parsed_name) && 0)
		return (ft_parse_line_header(str, e));
	else
		return (ft_parse_line_source_code(str, e));
}

int		ft_parse_asm(char *str, t_env *e)
{
	char *line;
	int fd;
	(void)e;

	if ((fd = open(str , O_RDONLY)) == -1)
	{
		perror(str);
		return (1);
	}
	else if ((read_name_file(str, e)) == 1)
	{
		ft_log_error_no_line("File must be of extension \'.s\'", e);
		return (1);
	}
	while (get_next_line(fd, &line))
	{
		e->parser.nb_line++;
		if (ft_is_relevant(line)) // pas une ligne vide ou un commentaire
		{
			if (ft_parse_line(line, e))
			{
				ft_lstdel_value(&(e->champ.instructions));
				return (1);
			}
		}
		free(line);
	}
//	ft_print_instructions(e->champ.instructions);
	free(line);
	close(fd);
	return (0);
}
