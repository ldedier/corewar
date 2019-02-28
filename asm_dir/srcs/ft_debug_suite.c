/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:45:00 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/27 12:45:07 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
