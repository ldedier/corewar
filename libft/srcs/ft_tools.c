/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:04:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/28 21:22:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_no_number(t_pf *pf)
{
	pf->parse_padding = 0;
	pf->parse_precision = 0;
}

intmax_t	ft_abs_max(intmax_t a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

double		ft_fabs(double a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}
