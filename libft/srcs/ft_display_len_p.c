/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_len_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 23:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:20:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_len_p(t_pf pf)
{
	intmax_t res;

	if (pf.var.integer == 0)
	{
		if (pf.precised_precision)
			return (2 + pf.flags.precision);
		else
			return (3);
	}
	res = 1;
	while (pf.var.integer / 16 != 0)
	{
		pf.var.integer /= 16;
		res++;
	}
	return (ft_max(3, res + 2));
}
