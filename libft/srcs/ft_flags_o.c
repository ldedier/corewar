/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:23:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:04:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_o(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	get_casted_value_unsigned(pf, va);
	no_padding_bytes = ft_pf_len_o(*pf);
	if (pf->precised_precision && pf->flags.padding_style != e_padding_negative)
		pf->flags.padding_style = e_padding_standard;
	ft_add_padding_pre(pf, no_padding_bytes);
	if (pf->flags.display_style)
		ft_putchar_buff('0', pf);
	ft_add_precision_o(pf);
	if ((!pf->precised_precision || pf->flags.precision || pf->var.integer)
		&& !(pf->flags.display_style && pf->var.integer == 0
			&& pf->flags.precision <= 1))
		ft_putoctal_max(pf->var.integer, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_o_maj(t_pf *pf, va_list va, char c)
{
	(void)c;
	pf->flags.length_mod = e_mod_long_int;
	return (ft_pf_o(pf, va, c));
}
