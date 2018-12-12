/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:38:14 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 19:37:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			mod(int val, int max)
{
	return (val % max);
}

int		ft_pow(int n, int pow) // remove
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

t_process *get_proc_num(t_list *lst, int num)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (((t_process *)(tmp->content))->id == num)
			return ((t_process *)(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

t_process *get_proc_index(t_list *lst, int index)
{
	t_list	*tmp;

	tmp = lst;
	while (index-- >= 0)
		tmp = tmp->next;
	return ((t_process *)(tmp->content));
}

