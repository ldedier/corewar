/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:07:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 15:37:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

void	ft_free_instruction_des(t_instruction *instruction)
{
	if (instruction->label)
		free(instruction->label);
	free(instruction);
}

void	ft_free_instruction_des_tlst(void *instruction, size_t dummy)
{
	(void)dummy;
	ft_free_instruction_des(instruction);
}

void	ft_free_all(t_env *e)
{
	if (e->champ.assembly_name)
		free(e->champ.assembly_name);
	ft_lstdel(&(e->champ.instructions), &ft_free_instruction_des_tlst);
}
