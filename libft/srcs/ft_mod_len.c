/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:21:48 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 22:00:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_h(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	if (pf->flags.length_mod <= e_mod_short_int)
	{
		if (pf->flags.length_mod == e_mod_short_int)
			pf->flags.length_mod = e_mod_signed_char;
		else
			pf->flags.length_mod = e_mod_short_int;
	}
	return (0);
}

int		ft_pf_l(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	if (pf->flags.length_mod <= e_mod_long_long_int)
	{
		if (pf->flags.length_mod == e_mod_long_int)
			pf->flags.length_mod = e_mod_long_long_int;
		else
			pf->flags.length_mod = e_mod_long_int;
	}
	return (0);
}

int		ft_pf_j(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	pf->flags.length_mod = e_mod_intmax_t;
	return (0);
}

int		ft_pf_z(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	if (pf->flags.length_mod < e_mod_size_t)
		pf->flags.length_mod = e_mod_size_t;
	return (0);
}
