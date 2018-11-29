/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:34:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:04:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_point(t_pf *pf, va_list va, char c)
{
	(void)c;
	(void)va;
	ft_no_number(pf);
	pf->parse_precision = 1;
	pf->precised_precision = 1;
	pf->flags.precision = 0;
	return (0);
}

int		ft_pf_digit(t_pf *pf, va_list va, char c)
{
	(void)va;
	if (pf->parse_padding)
		pf->flags.padding = pf->flags.padding * 10 + c - '0';
	else if (pf->parse_precision)
		pf->flags.precision = pf->flags.precision * 10 + c - '0';
	else
	{
		pf->parse_padding = 1;
		pf->flags.padding = c - '0';
	}
	return (0);
}

int		ft_pf_0(t_pf *pf, va_list va, char c)
{
	(void)va;
	if (!pf->parse_padding && !pf->parse_precision &&
			pf->flags.padding_style != e_padding_negative)
		pf->flags.padding_style = e_padding_zeros;
	return (ft_pf_digit(pf, va, c));
}

int		ft_pf_percent(t_pf *pf, va_list va, char c)
{
	(void)c;
	(void)va;
	ft_add_padding_pre(pf, 1);
	ft_putchar_buff('%', pf);
	ft_add_padding_post(pf, 1);
	return (1);
}
