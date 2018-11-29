/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 22:53:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_ullint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned long long int)va_arg(va, intmax_t);
}

void	ft_gtvar_uintmax_t(t_pf *pf, va_list va)
{
	pf->var.integer = (uintmax_t)va_arg(va, intmax_t);
}

void	ft_gtvar_ushort_int(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned short int)va_arg(va, intmax_t);
}
