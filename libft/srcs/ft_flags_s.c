/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:32:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:08:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_s(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	if (pf->flags.length_mod == e_mod_long_int)
		return (ft_pf_s_maj(pf, va, c));
	pf->var.str = va_arg(va, char *);
	if (pf->var.str == NULL)
		pf->var.str = "(null)";
	no_padding_bytes = ft_pf_len_s(*pf);
	ft_add_padding_pre(pf, no_padding_bytes);
	ft_putnstr(pf->var.str, no_padding_bytes, pf);
	ft_add_padding_post(pf, no_padding_bytes);
	return (1);
}

int		ft_pf_s_maj(t_pf *pf, va_list va, char c)
{
	int no_padding_bytes;

	(void)c;
	pf->var.wstr = va_arg(va, int *);
	if (pf->var.wstr == NULL)
	{
		pf->var.str = "(null)";
		no_padding_bytes = ft_pf_len_s(*pf);
		ft_add_padding_pre(pf, no_padding_bytes);
		ft_putnstr(pf->var.str, no_padding_bytes, pf);
		ft_add_padding_post(pf, no_padding_bytes);
	}
	else
	{
		if (ft_has_forbidden_values(*pf))
			return (-1);
		no_padding_bytes = ft_pf_len_s_maj(*pf);
		ft_add_padding_pre(pf, no_padding_bytes);
		ft_putwnstr(pf->var.wstr, no_padding_bytes, pf);
		ft_add_padding_post(pf, no_padding_bytes);
	}
	return (1);
}
