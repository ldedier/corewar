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


int		ft_describe_label(char *str, int n, t_env *e)
{
	int i;

	i = 0;
	while (str[i] && i < n)
	{
		ft_printf("%c", str[i]);
		if (!ft_is_in_str(LABEL_CHARS, str[i]))
		{
			ft_log_error(LEXICAL_ERROR, i, e);
			return (0);
		}
		i++;
	}
	ft_printf("\n");
	return (1);
}

int		ft_parse_label_or_opcode(char *str, t_env *e)
{
	int start;
	int i;
	start = 0;
	while (ft_isseparator(str[start]))
		start++;
	i = start;
	while (str[i] && str[i] != ' ' && str[i] != LABEL_CHAR)
		i++;
	if (!str[i])
		return (ft_log_error(LEXICAL_ERROR, i, e));
	else if (str[i] == ':')
	{
		e->parser.column_offset = start;
		if (ft_describe_label(&(str[start]), i, e))
			return (0);
		else
			return (1);
	}
	return (0);
}

int		ft_parse_line_source_code(char *str, t_env *e)
{
	ft_reset_parser(&(e->parser), str);
	if (!(e->parser.current_instruction = ft_append_new_instruction(e)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (ft_parse_label_or_opcode(str, e))
		return (1);
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
