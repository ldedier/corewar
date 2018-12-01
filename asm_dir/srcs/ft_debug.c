/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:53:52 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/01 16:54:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_print_param(t_parameter param)
{
	if (param.type & T_DIR)
	{
		ft_printf("direct: ");
		if (param.type & T_LAB)
		{
			ft_printf("(label): ");
			ft_printf("%s\n", param.label_name);
		}
		else
			ft_printf("%d\n", param.value);
		return ;

	}
	else if (param.type & T_REG)
		ft_printf("register: ");
	else if (param.type & T_IND)
		ft_printf("indirect: ");
	ft_printf("%d\n", param.value);
}

void	ft_print_instruction(t_instruction *instruction)
{
	int i;

	i = 0;
	ft_printf(RED"instruction line %d:\n"EOC, instruction->nb_line);
	ft_printf("address: %d\n", instruction->address);
	ft_printf("opcode: %d\n", instruction->opcode);
	ft_printf("Octet de Codage des Parametres: %d\n", instruction->ocp);
	ft_printf("nb_params: %d\n", instruction->nb_params);
	
	while (i < instruction->nb_params)
	{
		ft_print_param(instruction->params[i]);
		i++;
	}
	ft_printf("\n");
}

void	ft_print_instructions(t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instruction;

	ptr = instructions;
	while (ptr != NULL)
	{
		instruction = ptr->content;
		ft_print_instruction(instruction);
		ptr = ptr->next;
	}
}
