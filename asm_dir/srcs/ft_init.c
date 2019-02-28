/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:10:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 01:11:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_init_champion(t_champion *champ, char *filename)
{
	champ->assembly_name = filename;
	champ->cor_name = NULL;
	champ->instructions = NULL;
	champ->labels = NULL;
	champ->header.magic = COREWAR_EXEC_MAGIC;
	champ->header.prog_size = 0;
	ft_bzero(champ->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->header.comment, COMMENT_LENGTH + 1);
}

void		ft_init_parameter(t_parameter *parameter)
{
	parameter->type = 0;
	parameter->value = 0;
	parameter->source_code_col = 0;
	parameter->label_name = NULL;
}

void	ft_init_env(t_env *e, char *filename)
{
	ft_init_champion(&(e->champ), filename);
	ft_init_parser(&(e->parser));
}

int			ft_init_instruction(t_instruction *instruction, t_env *e)
{
	int		i;

	instruction->op = NULL;
	instruction->address = e->champ.header.prog_size;
	instruction->nb_line = e->parser.nb_line;
	instruction->ocp = 0;
	i = 0;
	while (i < 3)
	{
		ft_init_parameter(&(instruction->params[i]));
		i++;
	}
	if (!(instruction->source_code_line = ft_strdup(e->parser.current_line)))
		return (1);
	return (0);
}
