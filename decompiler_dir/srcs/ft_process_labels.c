/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_labels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:30:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/10 19:13:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

void	ft_update_labeled_to(t_instruction *instru, int param_index,
			t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instru_iter;

	ptr = instructions;
	while (ptr != NULL)
	{
		instru_iter = (t_instruction *)ptr->content;
		if (instru_iter->address == instru->address
				+ (short)(instru->params[param_index].value))
		{
			instru_iter->is_labeled = 1;
			instru->params[param_index].labeled_to = instru_iter;
			return ;
		}
		ptr = ptr->next;
	}
	instru->params[param_index].labeled_to = NULL;
}

int		ft_process_asm_labels(t_env *e)
{
	t_list			*ptr;
	t_instruction	*instru;
	int				i;
	int				op;

	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instru = (t_instruction *)ptr->content;
		op = instru->op->opcode;
		i = 0;
		while (i < instru->op->nb_params)
		{
			if (instru->params[i].type != REG_CODE
				&& ((i == 0 && (op == FORK || op == ZJMP || op == LDI))
					|| (i == 1 && (op == STI || op == ST))))
				ft_update_labeled_to(instru, i, e->champ.instructions);
			else
				instru->params[i].labeled_to = NULL;
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}

int		ft_attribute_label(t_instruction *instruction, int nb_instr)
{
	char	*nb_str;
	char	*label;

	if (!(nb_str = ft_itoa(nb_instr)))
		return (1);
	if (nb_instr <= 9)
	{
		if (!(label = ft_strjoin_3("label", "0", nb_str)))
		{
			free(nb_str);
			return (1);
		}
	}
	else
	{
		if (!(label = ft_strjoin("label", nb_str)))
		{
			free(nb_str);
			return (1);
		}
	}
	free(nb_str);
	instruction->label = label;
	return (0);
}

int		ft_attribute_asm_labels(t_env *e)
{
	t_list			*ptr;
	t_instruction	*instru;
	int				i;

	i = 0;
	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instru = (t_instruction *)ptr->content;
		if (instru->is_labeled)
		{
			if (ft_attribute_label(instru, i++))
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
