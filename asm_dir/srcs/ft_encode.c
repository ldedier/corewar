/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 00:59:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 16:10:07 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_encode_header(int fd, t_env *e)
{
	int total;

	total = 0;
	total += ft_write(fd, e->champ.header.magic, sizeof(e->champ.header.magic));
	total += write(fd, e->champ.header.prog_name,
											sizeof(e->champ.header.prog_name));
	ft_add_padding(fd, total);
	total += ft_write(fd, e->champ.header.prog_size,
											sizeof(e->champ.header.prog_size));
	write(fd, e->champ.header.comment, sizeof(e->champ.header.comment));
	ft_add_padding(fd, total);
}

void		ft_encode_param(int fd, t_instruction *instruction, int index)
{
	if (instruction->params[index].type & T_REG)
		ft_write(fd, instruction->params[index].value, E_REG);
	else if (instruction->params[index].type & T_IND)
		ft_write(fd, instruction->params[index].value, E_IND);
	else if (instruction->params[index].type & T_DIR)
	{
		if (instruction->op->describe_address)
			ft_write(fd, instruction->params[index].value, E_IND);
		else
			ft_write(fd, instruction->params[index].value, E_DIR);
	}
}

void		ft_encode_instruction(int fd, t_instruction *instruction)
{
	int i;

	i = 0;
	ft_write(fd, instruction->op->opcode, 1);
	if (instruction->op->has_ocp)
		ft_write(fd, instruction->ocp, 1);
	while (i < instruction->op->nb_params)
	{
		ft_encode_param(fd, instruction, i);
		i++;
	}
}

void		ft_process_encoding(int fd, t_env *e)
{
	t_list			*ptr;
	t_instruction	*instruction;

	ft_encode_header(fd, e);
	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instruction = (t_instruction *)(ptr->content);
		ft_encode_instruction(fd, instruction);
		ptr = ptr->next;
	}
}

int			ft_encode_to_cor(char *filename, t_env *e)
{
	int fd;

	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		perror(filename);
		return (1);
	}
	ft_process_encoding(fd, e);
	close(fd);
	return (0);
}
