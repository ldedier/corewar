/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:53:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 16:08:56 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_print_param_suite(t_parameter param)
{
	if (param.type & T_IND)
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
	ft_print_param_suite(param);
}

void	ft_print_op(t_op *op)
{
	ft_printf("opcode: %#04x\n", op->opcode);
}

void	ft_print_instruction(t_instruction *instruction)
{
	int i;

	i = 0;
	ft_printf(RED"instruction line %d:\n"EOC, instruction->nb_line);
	ft_printf("address: %d\n", instruction->address);
	ft_print_op(instruction->op);
	if (instruction->op->has_ocp)
		ft_printf("Octet de Codage des Parametres: %#04x (%08b)\n",
										instruction->ocp, instruction->ocp);
	while (i < instruction->op->nb_params)
	{
		ft_print_param(instruction->params[i], i + 1);
		i++;
	}
	ft_printf("\n");
}
