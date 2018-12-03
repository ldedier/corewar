/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:53:52 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 00:12:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_print_param(t_parameter param, int index)
{
	ft_printf("parameter #%d\n", index);
	if (param.type & T_DIR)
	{
		ft_printf("direct: ");
		if (param.type & T_LAB)
		{
			ft_printf("(label): ");
			ft_printf("%s\n", param.label_name);
		}
		ft_printf("%d\n", param.value);
		return ;
	}
	else if (param.type & T_IND)
	{
		ft_printf("indirect: ");
		if (param.type & T_LAB)
		{
			ft_printf("(label): ");
			ft_printf("%s\n", param.label_name);
		}
		ft_printf("%d\n", param.value);
	}

	else if (param.type & T_REG)
	{
		ft_printf("register: ");
		ft_printf("%d\n", param.value);
	}
}

void	ft_print_op(t_op op)
{
	ft_printf("opcode: %#04x\n",  op.opcode);
}

void	ft_print_instruction(t_instruction *instruction)
{
	int i;

	i = 0;
	ft_printf(RED"instruction line %d:\n"EOC, instruction->nb_line);
	ft_printf("address: %d\n", instruction->address);
	ft_print_op(instruction->op);
	if (instruction->op.has_ocp)
		ft_printf("Octet de Codage des Parametres: %#04x (%08b)\n", instruction->ocp,
		instruction->ocp);

	while (i < instruction->op.nb_params)
	{
		ft_print_param(instruction->params[i], i + 1);
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

void	ft_print_label(t_label *label)
{
	ft_printf(CYAN"%s\n"EOC, label->name);
	ft_printf("%d\n\n", label->address);
}

void	ft_print_labels(t_list *labels)
{
	t_list			*ptr;
	t_label			*label;

	ptr = labels;
	while (ptr != NULL)
	{
		label = ptr->content;
		ft_print_label(label);
		ptr = ptr->next;
	}

}
