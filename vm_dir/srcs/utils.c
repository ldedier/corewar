/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:38:14 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/25 15:30:42 by emuckens         ###   ########.fr       */
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
//	res = val < 0 ? (val + max) % max : val % max;
	return (res);
}

/*
** is_reg function tests if the given number is a valid registry number
*/

int			is_reg(int num)
{
	return (num >= 1 && num <= REG_NUMBER);
}
