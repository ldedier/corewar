/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:54:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:11:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned(unsigned int nb, t_pf *pf)
{
	if ((nb / 10) == 0)
		ft_putchar_buff(nb % 10 + '0', pf);
	else
	{
		ft_putnbr_unsigned(nb / 10, pf);
		ft_putchar_buff(nb % 10 + '0', pf);
	}
}
