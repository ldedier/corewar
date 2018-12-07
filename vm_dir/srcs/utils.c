/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:38:14 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 16:54:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			mod(int val, int max)
{
	return (val % max);
}

int		ft_pow(int n, int pow)
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
