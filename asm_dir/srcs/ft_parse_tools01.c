/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:26:08 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/25 16:18:15 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_process_nb_params_coherent(int *save, t_env *e, char c)
{
	if (!e->parser.parse_param && !ft_isseparator(c) && c != SEPARATOR_CHAR)
		e->parser.parse_param = 1;
	if (c == SEPARATOR_CHAR)
	{
		if (!e->parser.parse_param)
		{
			if (*save != -1)
				e->parser.column_offset = *save;
			else
				e->parser.column_offset--;
			ft_log_error("empty argument", 0, e);
			return (1);
		}
		*save = e->parser.column_offset;
		e->parser.parse_param = 0;
		e->parser.nb_params += 1;
		if (e->parser.nb_params > e->parser.current_instruction->op->nb_params)
		{
			ft_log_custom_nb_params_error(e);
			return (1);
		}
	}
	return (0);
}

int				ft_nb_params_coherent(char *str, t_env *e)
{
	int		i;
	int		save;

	save = -1;
	e->parser.nb_params = 0;
	e->parser.parse_param = 0;
	i = 0;
	while (str[i] && ft_addco(str[i], e))
	{
		if (ft_process_nb_params_coherent(&save, e, str[i]))
			return (0);
		i++;
	}
	if (e->parser.parse_param && ++e->parser.nb_params ==
			e->parser.current_instruction->op->nb_params)
		return (1);
	else
	{
		ft_log_custom_nb_params_error(e);
		return (0);
	}
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

int				ft_addco(char c, t_env *e)
{
	if (c == '\t')
	{
		e->parser.column_offset += TAB_SIZE -
			(e->parser.column_offset % TAB_SIZE);
	}
	else
		e->parser.column_offset++;
	return (1);
}

int				ft_is_atouiable(char *s)
{
	long	res;
	int		start;
	int		i;

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
