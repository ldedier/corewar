/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:16:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:19:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_len_s(t_pf pf)
{
	if (pf.precised_precision)
		return (ft_min(pf.flags.precision, ft_strlen(pf.var.str)));
	else
		return (ft_strlen(pf.var.str));
}

int	ft_pf_len_s_maj(t_pf pf)
{
	if (pf.precised_precision)
		return (ft_wstrlen_prec(pf.var.wstr, pf.flags.precision));
	else
		return (ft_wstrlen(pf.var.wstr));
}
