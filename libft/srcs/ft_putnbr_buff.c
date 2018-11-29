/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:05:32 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:24:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_buff(int n, t_pf *pf)
{
	unsigned int nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar_buff('-', pf);
	}
	else
		nb = n;
	if ((nb / 10) == 0)
		ft_putchar_buff(nb % 10 + '0', pf);
	else
	{
		ft_putnbr_buff(nb / 10, pf);
		ft_putchar_buff(nb % 10 + '0', pf);
	}
}
