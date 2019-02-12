/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:30:46 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/08 18:37:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_process_parse_params(char **params_split, t_env *e)
{
	int		i;
	int		save;

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

int		ft_process_populate_from_opcode(char *opcode_str, t_env *e)
{
	int		i;

	i = 0;
	while (i < NB_INSTRUCTIONS)
	{
		if (!ft_strcmp(opcode_str, g_op_tab[i].instruction_name))
		{
			e->parser.current_instruction->op = &g_op_tab[i];
			free(opcode_str);
			return (0);
		}
		i++;
	}
	free(opcode_str);
	return (1);
}

int		ft_process_parse_indirect_value(char *str, int index, int offset, t_env *e)
{
	int		ret;
	char	*str2;
	int		i;

	i = 0;
	str2 = str;
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	else if (!ft_is_atouiable(str))
		return (ft_log_error(EXCESSIVE_VALUE, offset, e));
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	//if (ret < 0 || ret > REG_NUMBER)
	//	return (ft_log_error(INVALID_IND_NUMBER, offset + 1, e));
	e->parser.current_instruction->params[index].value = ret;
	e->parser.column_offset += str + 1 - str2;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int		ft_process_parse_direct_value(char *str, int index, int offset, t_env *e)
{
	int		ret;
	char	*str2;
	int		i;

	i = 0;
	str2 = str;
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	else if (!ft_is_atouiable(str))
		return (ft_log_error(EXCESSIVE_VALUE, offset, e));
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	//	if (ret < 0 || ret > REG_NUMBER)
	//		return (ft_log_error(INVALID_IND_NUMBER, offset + 1, e));
	e->parser.current_instruction->params[index].value = ret;
	e->parser.column_offset += str - str2 + 1;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int		ft_process_parse_indirect(char *str, int index, t_env *e)
{
	e->champ.header.prog_size += E_IND;
	e->parser.current_instruction->params[index].nb_bytes = E_IND;
	e->parser.current_instruction->ocp |= (IND_CODE << (6 - (2 * index)));
	if (!(T_IND & e->parser.current_instruction->op->arg_types[index]))
		return (ft_log_custom_wrong_param_type("indirect", index, 0, e));
	e->parser.current_instruction->params[index].type |= T_IND;
	if (str[0] == LABEL_CHAR)
		return (ft_process_parse_label(&(str[1]), index, 1, e));
	else
		return (ft_process_parse_indirect_value(str, index, 0, e));
}
