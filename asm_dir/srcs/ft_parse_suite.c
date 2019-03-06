/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:23:19 by cammapou          #+#    #+#             */
/*   Updated: 2019/03/06 19:03:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//	if (e->champ.header.prog_size > CHAMP_MAX_SIZE) //42_wrong.s
//		return (ft_log_error(TOO_BIG_CHAMP, 0, e));

int		ft_parse_param(char *str, int index, t_env *e)
{
	int i;
	int ret;

	i = 0;
	while (ft_isseparator(str[i]) && ft_addco(str[i], e))
		i++;
	ret = ft_process_parse_param(&(str[i]), index, e);
	return (ret);
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

int		ft_parse_instruction(char *str, t_env *e)
{
	int start;
	int i;

	start = 0;
	while (ft_isseparator(str[start]) && ft_addco(str[start], e))
		start++;
	i = start;
	while (str[i] && !ft_isseparator(str[i]) && str[i] != DIRECT_CHAR && 
				str[i] != LABEL_CHAR)
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
