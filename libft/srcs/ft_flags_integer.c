/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:35:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 10:44:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_d(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value(pf, va);
	no_padding_bytes = ft_pf_len_d(*pf);
	ft_add_padding_pre_standard(pf, no_padding_bytes);
	ft_add_prefix(pf);
	if (pf->var.integer < 0)
		ft_putchar_buff('-', pf);
	ft_add_padding_pre_zeros(pf, no_padding_bytes);
	ft_add_precision_base(pf, 10);
	if (!pf->precised_precision || pf->flags.precision || pf->var.integer)
		ft_putnbr_max(ft_abs_max(pf->var.integer), pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_d_maj(t_pf *pf, va_list va, char c)
{
	ft_pf_l(pf, va, c);
	return (ft_pf_d(pf, va, c));
}

int		ft_pf_u(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value_unsigned(pf, va);
	if (pf->precised_precision && pf->flags.padding_style != e_padding_negative)
		pf->flags.padding_style = e_padding_standard;
	no_padding_bytes = ft_pf_len_u(*pf);
	ft_add_padding_pre(pf, no_padding_bytes);
	ft_add_precision_base(pf, 10);
	if (!pf->precised_precision || pf->flags.precision || pf->var.integer)
		ft_putnbr_max(pf->var.integer, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_u_maj(t_pf *pf, va_list va, char c)
{
	ft_pf_l(pf, va, c);
	return (ft_pf_u(pf, va, c));
}

int		ft_pf_c(t_pf *pf, va_list va, char c)
{
	if (pf->flags.length_mod == e_mod_long_int)
		return (ft_pf_c_maj(pf, va, c));
	pf->var.integer = va_arg(va, int);
	ft_add_padding_pre(pf, 1);
	ft_putchar_buff(pf->var.integer, pf);
	ft_add_padding_post(pf, 1);
	return (1);
}
