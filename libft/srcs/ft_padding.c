/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:07:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 03:58:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_padding_pre(t_pf *pf, int no_padding_byte)
{
	int i;

	i = 0;
	if (pf->flags.padding_style == e_padding_standard)
	{
		while (i < pf->flags.padding - no_padding_byte)
		{
			ft_putchar_buff(' ', pf);
			i++;
		}
	}
	else if (pf->flags.padding_style == e_padding_zeros)
	{
		while (i < pf->flags.padding - no_padding_byte)
		{
			ft_putchar_buff('0', pf);
			i++;
		}
	}
}

void	ft_add_padding_post(t_pf *pf, int no_padding_byte)
{
	int i;

	if (pf->flags.padding_style == e_padding_negative)
	{
		i = 0;
		while (i < pf->flags.padding - no_padding_byte)
		{
			ft_putchar_buff(' ', pf);
			i++;
		}
	}
}

void	ft_add_padding_pre_standard(t_pf *pf, int no_padding_byte)
{
	int i;

	if (pf->flags.padding_style == e_padding_standard ||
			(pf->precised_precision && pf->flags.padding_style
				!= e_padding_negative))
	{
		i = 0;
		while (i < pf->flags.padding - no_padding_byte)
		{
			ft_putchar_buff(' ', pf);
			i++;
		}
	}
}

void	ft_add_padding_pre_zeros(t_pf *pf, int no_padding_byte)
{
	int i;

	if (pf->flags.padding_style == e_padding_zeros && (!pf->precised_precision))
	{
		i = 0;
		while (i < pf->flags.padding - no_padding_byte)
		{
			ft_putchar_buff('0', pf);
			i++;
		}
	}
}

int		ft_pf_minus(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	pf->flags.padding_style = e_padding_negative;
	return (0);
}
