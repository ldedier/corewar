/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_x_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:45:41 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:02:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_p(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	pf->var.integer = (intmax_t)va_arg(va, void *);
	no_padding_bytes = ft_pf_len_p(*pf);
	ft_add_padding_pre_standard(pf, no_padding_bytes);
	ft_putnstr("0x", 2, pf);
	ft_add_padding_pre_zeros(pf, no_padding_bytes);
	ft_add_precision_base(pf, 16);
	if (pf->var.integer != 0 ||
			(!pf->precised_precision) || (pf->flags.precision != 0))
		ft_puthex_max(pf->var.integer, 0, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_x(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value_unsigned(pf, va);
	no_padding_bytes = ft_pf_len_x(*pf);
	ft_add_padding_pre_standard(pf, no_padding_bytes);
	if (pf->flags.display_style && pf->var.integer != 0)
		ft_putnstr("0x", 2, pf);
	ft_add_padding_pre_zeros(pf, no_padding_bytes);
	ft_add_precision_base(pf, 16);
	if (pf->var.integer || (!pf->precised_precision || pf->flags.precision))
		ft_puthex_max(pf->var.integer, 0, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_x_maj(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value_unsigned(pf, va);
	no_padding_bytes = ft_pf_len_x(*pf);
	ft_add_padding_pre_standard(pf, no_padding_bytes);
	if (pf->flags.display_style && pf->var.integer != 0)
		ft_putnstr("0X", 2, pf);
	ft_add_padding_pre_zeros(pf, no_padding_bytes);
	ft_add_precision_base(pf, 16);
	if (pf->var.integer || (!pf->precised_precision || pf->flags.precision))
		ft_puthex_max(pf->var.integer, 1, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}
