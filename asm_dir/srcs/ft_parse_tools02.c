/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:00:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 17:01:01 by ldedier          ###   ########.fr       */
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
	if (e->parser.current_instruction->op->has_ocp)
		e->champ.header.prog_size++;
	e->parser.column_offset += i - start;
	return (ft_parse_params(str, i, e));
}

int			ft_parse_params(char *str, int i, t_env *e)
{
	char	**params_split;
	int		save;
	int		len;

	len = ft_strlen(e->parser.current_instruction->op->instruction_name);
	save = e->parser.column_offset;
	if (!str[i])
	{
		e->parser.column_offset = save;
		return (ft_log_error(NO_PARAMETERS, -len, e));
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
