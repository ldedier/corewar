/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_to_assembly.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:08:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 01:26:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_encode_asm(int fd, t_env *e)
{
	t_list			*instructions;
	t_instruction	instruction;
	int				i;
	int				ret;

	instructions = NULL;
	i = 0;
	while (((ret = get_instruction(e->player.algo, &instruction,
			i, e->player.algo_len))) && i < e->player.algo_len)
	{
		instruction.address = i;
		instruction.is_labeled = 0;
		if (ft_add_to_list_back(&instructions, &instruction,
			sizeof(t_instruction)))
		{
			ft_lstdel_value(&instructions);
			return (1);
		}
		i += ret;
	}
	if (i != e->player.algo_len)
	{
		ft_lstdel_value(&instructions);
		return (1);
	}
	else
		return (ft_process_encode_asm(fd, instructions, e));
}

void	ft_update_labeled_to(t_instruction *instru, int param_index,
			t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instru_iter;

	ptr = instructions;
	while (ptr != NULL)
	{
		instru_iter = (t_instruction *)ptr->content;
		if (instru_iter->address == instru->address + (short)
				(instru->params[param_index].value))
		{
			instru_iter->is_labeled = 1;
			instru->params[param_index].labeled_to = instru_iter;
			return ;
		}
		ptr = ptr->next;
	}
	instru->params[param_index].labeled_to = NULL;
}

int		ft_process_asm_labels(t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instru;
	int i;

	ptr = instructions;
	while (ptr != NULL)
	{
		instru = (t_instruction *)ptr->content;
		i = 0;
		while (i < instru->op.nb_params)
		{
			if (instru->params[i].type != REG_CODE &&
				((i == 0 && (instru->op.opcode == FORK ||
				instru->op.opcode == ZJMP || instru->op.opcode == LDI))
					|| (i == 1 && instru->op.opcode == STI)))
				ft_update_labeled_to(instru, i, instructions);
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
	instruction->label = label;
	return (0);
}

int		ft_attribute_asm_labels(t_list *instructions)
{
	t_list			*ptr;
	t_instruction	*instru;
	int				i;

	i = 0;
	ptr = instructions;
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

int		ft_process_encode_asm(int fd, t_list *instructions, t_env *e)
{
	if (e->create_labels)
	{
		if (ft_process_asm_labels(instructions))
			return (1);
		if (ft_attribute_asm_labels(instructions))
			return (1);
	}
	ft_dprintf(fd, ".name \"%s\"\n", e->player.name);
	ft_dprintf(fd, ".comment \"%s\"\n\n", e->player.comm);
	return (ft_encode_instructions(fd, instructions, e->create_labels));
}


int		ft_encode_to_assembly(t_env *e)
{
	int fd;

	if ((fd = open(e->champ.assembly_name, O_RDWR | O_CREAT | O_TRUNC, 0644))
		== -1)
	{
		perror(e->champ.assembly_name);
		return (1);
	}
//	fd = 1;
	if (ft_encode_asm(fd, e))
		ft_printf("%s is wrongly encoded and could not be decompiled\n",
				e->champ.cor_name);
	else
		ft_printf("successfully decompiled %s at %s\n",
				e->champ.cor_name, e->champ.assembly_name);

	return (0);
}
