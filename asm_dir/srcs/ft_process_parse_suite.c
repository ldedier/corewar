/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_parse_suite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:32:49 by cammapou          #+#    #+#             */
/*   Updated: 2019/01/15 17:35:11 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_process_parse_direct(char *str, int index, int offset, t_env *e)
{
	if (e->parser.current_instruction->op.describe_address)
	{
		e->parser.current_instruction->params[index].nb_bytes = E_IND;
		e->champ.header.prog_size += E_IND;
	}
	else
	{
		e->parser.current_instruction->params[index].nb_bytes = E_DIR;
		e->champ.header.prog_size += E_DIR;
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
		return (ft_log_error(LEXICAL_ERROR, offset, e);
	return (0);
}

int		ft_process_parse_register(char *str, int index, int offset, t_env *e)
{
	int		ret;
	char	*str2;
	int		i;
	
	e->champ.header.prog_size += E_REG;
	e->parser.current_instruction->params[index].nb_bytes = E_REG;
	e->parser.current_instruction->ocp |= (REG_CODE << (6 - (2 * index)));
	i = 0;
	str2 = str;
	if (!(T_REG & e->parser.current_instruction->op.arg_types[index]))
		return (ft_log_custom_wrong_param_type("register", index, 0, e));
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, offset, e));
	else if (!ft_is_atouiable(str))
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
	char	*label_name;
	int		i;

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
