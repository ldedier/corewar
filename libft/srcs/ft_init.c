/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:51:48 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 03:57:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_nothing(t_pf *pf, va_list va, char c)
{
	(void)pf;
	(void)va;
	ft_add_padding_pre(pf, 1);
	ft_putchar_buff(c, pf);
	ft_add_padding_post(pf, 1);
	return (1);
}

void	ft_init_flags(t_flags *flags)
{
	flags->padding_style = e_padding_standard;
	flags->prefix = e_prefix_none;
	flags->length_mod = e_mod_none;
	flags->padding = 0;
	flags->precision = 0;
}

void	ft_init_pf(t_pf *pf)
{
	ft_init_flags(&(pf->flags));
	pf->parse_padding = 0;
	pf->parse_precision = 0;
	pf->precised_precision = 0;
	pf->flags.display_style = 0;
}
