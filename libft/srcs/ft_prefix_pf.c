/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:24:49 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 03:58:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_space(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	if (pf->flags.prefix != e_prefix_plus)
		pf->flags.prefix = e_prefix_blank;
	return (0);
}

int		ft_pf_plus(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	pf->flags.prefix = e_prefix_plus;
	return (0);
}

int		ft_pf_hashtag(t_pf *pf, va_list va, char c)
{
	(void)va;
	(void)c;
	pf->flags.display_style = 1;
	return (0);
}

void	ft_add_prefix(t_pf *pf)
{
	if (pf->var.integer >= 0)
	{
		if (pf->flags.prefix == e_prefix_plus)
			ft_putchar_buff('+', pf);
		else if (pf->flags.prefix == e_prefix_blank)
			ft_putchar_buff(' ', pf);
	}
}
