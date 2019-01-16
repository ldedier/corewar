/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:26:08 by cammapou          #+#    #+#             */
/*   Updated: 2019/01/15 23:53:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_nb_params_coherent(char *str, t_env *e)
{
	int	i;
	int	nb_params;

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

int		ft_addco(char c, t_env *e)
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

int		ft_is_atouiable(char *s)
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
