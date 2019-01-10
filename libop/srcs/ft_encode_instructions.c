/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:39:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/10 17:40:50 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int		ft_get_param_char(t_parameter *param)
{
	if (param->type == T_REG)
		return (REGISTER_CHAR);
	else if (param->type == T_DIR)
		return (DIRECT_CHAR);
	else
		return (0);
}

static void		ft_print_parameter(int fd, t_parameter *param)
{
	char c;

	c = ft_get_param_char(param);
	if (c)
		ft_dprintf(fd, " %c%d", c, param->value);
	else
		ft_dprintf(fd, " %d", param->value);
}

static int		ft_encode_instruction(int fd, t_instruction *instruction)
{
	int i;

	ft_dprintf(fd, "%s\t", instruction->op.instruction_name);
	i = 0;
	while (i < instruction->op.nb_params)
	{
		ft_print_parameter(fd, &instruction->params[i]);
		i++;
		if (i < instruction->op.nb_params)
			ft_dprintf(fd, "%c", SEPARATOR_CHAR);
	}
	ft_dprintf(fd, "\n");
	return (0);
}

int				ft_encode_instructions(int fd, t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instruction;

	ptr = instructions;
	while (ptr != NULL)
	{
		instruction = (t_instruction *)(ptr->content);
		ft_encode_instruction(fd, instruction);
		ptr = ptr->next;
	}
	return (0);
}
