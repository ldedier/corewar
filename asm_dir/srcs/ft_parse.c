/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:06:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/31 02:37:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_populate_from_opcode(char *str, int start, int i, t_env *e)
{
	char	*opcode_str;

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

int			ft_parse_params(char *str, int i, t_env *e)
{
	char	**params_split;
	int		save;

	save = e->parser.column_offset;
	if (!str[i])
	{
		e->parser.column_offset = save;
		return (ft_log_error(NO_PARAMETERS, -
			ft_strlen(e->parser.current_instruction->op.instruction_name), e));
	}
	if (!(params_split = ft_strsplit(&(str[i]), SEPARATOR_CHAR)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(ft_nb_params_coherent(&(str[i]), e)))
	{
		ft_free_split(params_split);
		return (1);
	}
	e->parser.column_offset = save;
	return (ft_process_parse_params(params_split, e));
}

int			ft_parse_line(char *str, t_env *e, int fd)
{
	char	*refined;
	int		ret;

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

int			ft_parse_asm(char *str, t_env *e)
{
	char	*line;
	int		ret;

	if ((e->parser.fd = open(str, O_RDONLY)) == -1)
	{
		perror(str);
		return (1);
	}
	else if ((ret = ft_switch_extension(str, ".s", ".cor", &(e->champ.cor_name))))
	{
		if (ret == -1)
			return (ft_log_error_no_line(MALLOC_ERROR, e));
		else
			return (ft_log_error_no_line("File must be of extension \'.s\'", e));
	}
	while (get_next_line(e->parser.fd, &line))
	{
		e->parser.nb_line++;
		if (ft_is_relevant(line)) // pas une ligne vide ou un commentaire
		{
			if (ft_parse_line(line, e, e->parser.fd) == 1)
			{
				free(line);
				return (1);
			}
		}
		free(line);
	}
	free(line);
	if (!e->parser.parsed_name)
	   return (ft_log_error_no_line("no name found", e));
	else if (!e->parser.parsed_comment)
	   return (ft_log_error_no_line("no comment found", e));
	else if (ft_fill_instructions_labels_values(e))
		return (1);
	else
	{
	//	ft_print_instructions(e->champ.instructions);
	//	ft_print_labels(e->champ.labels);
	//	ft_printf(":)\n");
		return (0);
	}
	close(e->parser.fd);
	return (0);
}
