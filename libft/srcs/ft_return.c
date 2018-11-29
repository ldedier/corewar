/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 22:33:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:14:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_add_return(int n)
{
	static int i = 0;

	i += n;
	return (i);
}

int		ft_reset_return(void)
{
	int res;

	res = ft_add_return(0);
	ft_add_return(-res);
	return (res);
}
