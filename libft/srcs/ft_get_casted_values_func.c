/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 22:54:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_long_long_int(t_pf *pf, va_list va)
{
	pf->var.integer = (long long int)va_arg(va, intmax_t);
}

void	ft_gtvar_intmax_t(t_pf *pf, va_list va)
{
	pf->var.integer = (intmax_t)va_arg(va, intmax_t);
}

void	ft_gtvar_uint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned int)va_arg(va, intmax_t);
}

void	ft_gtvar_uchar(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned char)va_arg(va, intmax_t);
}

void	ft_gtvar_ulint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned long int)va_arg(va, intmax_t);
}
