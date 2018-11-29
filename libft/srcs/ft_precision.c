/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:15:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 10:51:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_precision_base(t_pf *pf, int base)
{
	int nb_diff;
	int res;
	int	tmp;

	tmp = pf->var.integer;
	res = 1;
	while (tmp / base != 0)
	{
		tmp /= base;
		res++;
	}
	nb_diff = pf->flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0', pf);
		nb_diff--;
	}
}

void	ft_add_precision_o(t_pf *pf)
{
	int				nb_diff;
	int				res;
	unsigned int	tmp;

	tmp = pf->var.integer;
	res = 1 + pf->flags.display_style;
	while (tmp / 8 != 0)
	{
		tmp /= 8;
		res++;
	}
	nb_diff = pf->flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0', pf);
		nb_diff--;
	}
}

void	ft_add_precision_base_u(t_pf *pf, int base)
{
	int				nb_diff;
	int				res;
	unsigned int	nb;

	nb = pf->var.integer;
	res = 1;
	while (nb / base != 0)
	{
		nb /= base;
		res++;
	}
	nb_diff = pf->flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0', pf);
		nb_diff--;
	}
}
