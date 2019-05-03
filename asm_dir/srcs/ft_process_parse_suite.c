/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_parse_suite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:32:49 by cammapou          #+#    #+#             */
/*   Updated: 2019/03/14 23:49:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_process_parse_direct(char *str, int index, t_env *e)
{
	if (e->parser.current_instruction->op->describe_address)
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
	if (!(T_DIR & e->parser.current_instruction->op->arg_types[index]))
		return (ft_log_custom_wrong_param_type("direct", index, 0, e));
	e->parser.current_instruction->params[index].type |= T_DIR;
	if (str[0] == LABEL_CHAR)
		return (ft_process_parse_label(&(str[1]), index, 2, e));
	else
		return (ft_process_parse_dir_value(str, index, 1, e));
}

static int	ft_process_parse_register_suite(char *str, t_env *e)
{
	int	i;

	i = 0;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int			ft_process_parse_register(char *str, int index, t_env *e)
{
	int		ret;
	char	*str2;

	e->champ.header.prog_size += E_REG;
	e->parser.current_instruction->params[index].nb_bytes = E_REG;
	e->parser.current_instruction->ocp |= (REG_CODE << (6 - (2 * index)));
	str2 = str;
	if (!(T_REG & e->parser.current_instruction->op->arg_types[index]))
		return (ft_log_custom_wrong_param_type("register", index, 0, e));
	if (str[0] == '\0')
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	else if (!ft_is_atoiable(str))
		ft_log_warning(EXCESSIVE_VALUE, 1, e);
	ret = ft_patoui(&str);
	if (str == str2)
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	if (ret <= 0 || ret > REG_NUMBER)
		return (ft_log_custom_invalid_reg_number(1, e));
	e->parser.current_instruction->params[index].type = T_REG;
	e->parser.current_instruction->params[index].value = ret;
	e->parser.column_offset += str + 1 - str2;
	ft_process_parse_register_suite(str, e);
	return (0);
}

int			ft_process_parse_label(char *str, int index, int offset, t_env *e)
{
	char	*label_name;
	int		i;

	if (!(label_name = ft_get_str(&str)))
		ft_log_error(MALLOC_ERROR, offset, e);
	e->parser.current_instruction->params[index].source_code_col = offset
		+ e->parser.column_offset;
	e->parser.current_instruction->params[index].label_name = label_name;
	e->parser.current_instruction->params[index].type |= T_LAB;
	i = 0;
	e->parser.column_offset += ft_strlen(label_name) + offset;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	if (str[i])
		return (ft_log_error(LEXICAL_ERROR, 0, e));
	return (0);
}

int			ft_process_fill_instruction_label_value(t_instruction *instru,
		int index, t_list *labels)
{
	t_list	*ptr;
	t_label	*label;

	ptr = labels;
	while (ptr != NULL)
	{
		label = (t_label *)ptr->content;
		if (!ft_strcmp(instru->params[index].label_name, label->name))
		{
			if (instru->params[index].type & T_DIR)
				instru->params[index].value = label->address - instru->address;
			else
				instru->params[index].value = label->address - instru->address;
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}
