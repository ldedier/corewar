/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_to_assembly.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:08:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/16 16:31:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_process_encode_asm(int fd, t_list *instructions, t_env *e)
{
	ft_dprintf(fd, ".name \"%s\"\n", e->player.name);
	ft_dprintf(fd, ".comment \"%s\"\n\n", e->player.comm);
	return (ft_encode_instructions(fd, instructions));
}

int		ft_encode_asm(int fd, t_env *e)
{
	t_list			*instructions;
	t_instruction	instruction;
	int				i;
	int				ret;

	instructions = NULL;
	i = 0;
	while (((ret = get_instruction(e->player.algo, &instruction,
			i, e->player.algo_len)) != -1) && i < e->player.algo_len)
	{
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
		ft_printf("%s is wrongly encoded and could not be decompiled\n", e->champ.cor_name);
	else
		ft_printf("successfully decompiled %s at %s\n", e->champ.cor_name, e->champ.assembly_name);

	return (0);
}
