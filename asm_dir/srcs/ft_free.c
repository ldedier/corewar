/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 00:35:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 14:08:46 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_free_label(t_label *label)
{
	free(label->name);
	free(label);
}

void	ft_free_instruction(t_instruction *instruction)
{
	int	i;

	i = 0;
	if (instruction->op)
	{
		while (i < instruction->op->nb_params)
		{
			if (instruction->params[i].label_name)
				free(instruction->params[i].label_name);
			i++;
		}
	}
	free(instruction->source_code_line);
	free(instruction);
}

void	ft_free_label_tlst(void *label, size_t dummy)
{
	t_label *l;

	l = label;
	(void)dummy;
	ft_free_label(l);
}

void	ft_free_instruction_tlst(void *instruction, size_t dummy)
{
	(void)dummy;
	ft_free_instruction(instruction);
}

void	ft_free_all(t_env *e)
{
	int i;
	i = 0;
	if (e->champ.cor_name)
		free(e->champ.cor_name);
	ft_lstdel(&(e->champ.labels), &ft_free_label_tlst);
	ft_lstdel(&(e->champ.instructions), &ft_free_instruction_tlst);
}
