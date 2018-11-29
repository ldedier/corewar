/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:27:15 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:00:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_star(t_pf *pf, va_list va, char c)
{
	int val;

	(void)c;
	if (pf->parse_precision)
	{
		val = va_arg(va, int);
		if (val >= 0)
		{
			pf->precised_precision = 1;
			pf->flags.precision = val;
		}
		else
			pf->precised_precision = 0;
	}
	else
	{
		val = va_arg(va, int);
		pf->flags.padding = ft_abs_max(val);
		if (val < 0)
			pf->flags.padding_style = e_padding_negative;
	}
	return (0);
}

int		ft_pf_r(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	pf->var.str = va_arg(va, char *);
	if (pf->var.str == NULL)
		pf->var.str = "(null)";
	no_padding_bytes = ft_pf_len_s(*pf);
	ft_add_padding_pre(pf, no_padding_bytes);
	ft_putstr_non_printable(pf->var.str, no_padding_bytes, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_b(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value_unsigned(pf, va);
	if (pf->precised_precision && pf->flags.padding_style != e_padding_negative)
		pf->flags.padding_style = e_padding_standard;
	no_padding_bytes = ft_pf_len_b(*pf);
	ft_add_padding_pre(pf, no_padding_bytes);
	ft_add_precision_base(pf, 2);
	ft_putbin(pf->var.integer, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_n(t_pf *pf, va_list va, char c)
{
	int *data;

	(void)pf;
	(void)c;
	data = va_arg(va, int *);
	ft_empty_buffer(pf);
	*data = ft_add_return(0);
	return (1);
}
