/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:38:14 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/07 18:32:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			mod(int val, int max)
{
	int res;
	if (val >= 0)
		res = val % max;
	else
		res = (val + max) % max;
	return (res);
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

t_player	*get_player_num(t_vm *vm, t_list *lst, int num)
{
	int		i;

	(void)lst;
	i = -1;

	while (++i < MAX_PLAYERS)
		if (vm->player[i].num == num)
			return (&vm->player[i]);
	return (NULL);
}

/*
** get_proc_index function is used to get the wanted process' index in the list
** of all processes.
*/

t_process	*get_proc_index(t_list *lst, int index)
{
	t_list	*tmp;

	tmp = lst;
	while (index-- >= 0)
		tmp = tmp->next;
	return ((t_process *)(tmp->content));
}

/*
** is_reg function tests if the given number is a valid registry number
*/

int			is_reg(int num)
{
	return (num >= 1 && num <= REG_NUMBER);
}
