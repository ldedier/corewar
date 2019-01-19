/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:38:14 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/19 16:47:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			mod(int val, int max)
{
	return (val % max);
}

int			ft_pow(int n, int pow)
{
	int result;

	result = 1;
	if (pow <= 0)
		return (pow ? 0 : 1);
	while (pow >= 1)
	{
		result *= n;
		pow--;
	}
	return (result);
}

t_player *get_player_num(t_list *lst, int num)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("num = %d player num = %d\n", num, ((t_process *)tmp->content)->player->num);
		if (((t_process *)(tmp->content))->player->num == num)
			return (((t_process *)(tmp->content))->player);
		tmp = tmp->next;
	}
	return (NULL);
}

t_process	*get_proc_index(t_list *lst, int index)
{
	t_list	*tmp;

	tmp = lst;
	while (index-- >= 0)
		tmp = tmp->next;
	return ((t_process *)(tmp->content));
}

int				is_reg(int num)
{
	if (num >= 1 && num <= 16)
		return (1);
	else
		return (0);
}
