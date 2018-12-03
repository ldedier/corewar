/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 00:59:48 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 01:34:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_encode_header(int fd, t_env *e)
{
	write(fd, &(e->champ.header), sizeof(t_header));
}

void	ft_encode_param(int fd, t_instruction *instruction, int index)
{
	if (instruction->params[index].type & T_REG)
		write(fd, &(instruction->params[index].value), REG_SIZE);
	else if (instruction->params[index].type & T_IND)
		write(fd, &(instruction->params[index].value), IND_SIZE);
	else if (instruction->params[index].type & T_DIR)
	{
		if (instruction->op.describe_address)
			write(fd, &(instruction->params[index].value), IND_SIZE);
		else
			write(fd, &(instruction->params[index].value), DIR_SIZE);
	}
}

void	ft_encode_instruction(int fd, t_instruction *instruction)
{
	int i;

	i = 0;
	write(fd, &instruction->op.opcode, 1);
	if (instruction->op.has_ocp)
		write(fd, &(instruction->ocp), 1);
	while (i < instruction->op.nb_params)
	{
		ft_encode_param(fd, instruction, i);
		i++;
	}
}

void	ft_process_encoding(int fd, t_env *e)
{
	t_list *ptr;
	t_instruction *instruction;

	ft_encode_header(fd, e);
	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instruction = (t_instruction *)(ptr->content);
		ft_encode_instruction(fd, instruction);
		ptr = ptr->next;
	}
}

int		ft_encode_to_cor(char *filename, t_env *e)
{
	int fd;

	if ((fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
	{
		perror(filename);
		return (1);
	}
	ft_process_encoding(fd, e);
	close(fd);
	return (0);
}
