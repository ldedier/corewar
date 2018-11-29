/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_len_integer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 23:39:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:19:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_len_d(t_pf pf)
{
	int res;
	int sign;

	if (pf.var.integer < 0)
		sign = 1;
	else
		sign = 0;
	if (pf.var.integer == 0 && pf.precised_precision)
		return (pf.flags.precision + ((pf.flags.prefix > 0) ? 1 : 0));
	res = 1;
	while (pf.var.integer / 10 != 0)
	{
		pf.var.integer /= 10;
		res++;
	}
	if (pf.precised_precision == 1)
	{
		return (ft_max(res, pf.flags.precision) + sign +
			((pf.flags.prefix > 0) ? 1 : 0) * ((pf.var.integer < 0) ? 0 : 1));
	}
	else
		return (res + sign + ((pf.flags.prefix > 0) ? 1 : 0) *
		((pf.var.integer < 0) ? 0 : 1));
}

int		ft_pf_len_u(t_pf pf)
{
	int			res;
	uintmax_t	n;

	if (pf.var.integer == 0 && pf.precised_precision)
		return (pf.flags.precision);
	n = pf.var.integer;
	res = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		res++;
	}
	return (ft_max(res, pf.flags.precision));
}

int		ft_pf_len_b(t_pf pf)
{
	int			res;
	uintmax_t	n;

	n = pf.var.integer;
	res = 1;
	while (n / 2 != 0)
	{
		n /= 2;
		res++;
	}
	return (ft_max(res, pf.flags.precision));
}

int		ft_pf_len_o(t_pf pf)
{
	int			res;
	uintmax_t	n;

	if (pf.var.integer == 0 && pf.precised_precision)
		return (ft_max(pf.flags.precision, pf.flags.display_style));
	n = pf.var.integer;
	res = 1;
	while (n / 8 != 0)
	{
		n /= 8;
		res++;
	}
	if (pf.var.integer == 0)
		return (ft_max(res, pf.flags.display_style));
	else
		return (ft_max(res, pf.flags.precision - pf.flags.display_style)
			+ (pf.flags.display_style));
}

int		ft_pf_len_x(t_pf pf)
{
	int				res;
	unsigned int	nb;

	if (pf.var.integer == 0)
	{
		if (pf.precised_precision)
			return (pf.flags.precision);
		else
			return (1);
	}
	res = 1;
	nb = pf.var.integer;
	while ((nb / 16) != 0)
	{
		nb /= 16;
		res++;
	}
	return (ft_max(res, pf.flags.precision) +
		pf.flags.display_style * 2);
}
