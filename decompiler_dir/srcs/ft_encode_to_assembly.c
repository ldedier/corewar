/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_to_assembly.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:08:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/14 02:43:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_encode_asm(t_env *e)
{
	t_instruction	instruction;
	unsigned int	i;
	int				ret;

	i = 0;
	ft_bzero(&instruction, sizeof(t_instruction));
	while (((ret = read_ins(e->player.algo, &instruction, &i,
			e->player.algo_len))) && i <= (unsigned int)e->player.algo_len)
	{
		instruction.is_labeled = 0;
		instruction.label = NULL;
		if (ft_add_to_list_back(&e->champ.instructions, &instruction,
			sizeof(t_instruction)))
		{
			return (-1);
		}
		instruction.op = NULL;
		instruction.address = i;
	}
	if (i != (unsigned int)e->player.algo_len)
	{
		return (1);
	}
	else
		return (ft_process_encode_asm(e));
}

int		ft_process_encode_asm(t_env *e)
{
	int fd;

	if (e->create_labels)
	{
		ft_process_asm_labels(e);
		if (ft_attribute_asm_labels(e))
			return (-1);
	}
	if ((fd = open(e->champ.assembly_name, O_RDWR | O_CREAT | O_TRUNC, 0644))
		== -1)
	{
		perror(e->champ.assembly_name);
		return (3);
	}
	ft_dprintf(fd, ".name \"%s\"\n", e->player.name);
	ft_dprintf(fd, ".comment \"%s\"\n\n", e->player.comm);
	ft_encode_instructions(fd, e->champ.instructions, e->create_labels);
	close(fd);
	return (0);
}

int		ft_encode_to_assembly(t_env *e)
{
	int ret;

	if ((ret = ft_encode_asm(e)))
	{
		if (ret == 1)
			ft_printf("%s is wrongly encoded and could not be decompiled\n",
					e->champ.cor_name);
		else
			return (ft_return_verbosed("malloc error", 1));
	}
	else
		ft_printf("successfully decompiled %s at %s\n",
				e->champ.cor_name, e->champ.assembly_name);
	return (ret);
}
