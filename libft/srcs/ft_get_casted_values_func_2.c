/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 22:53:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_none(t_pf *pf, va_list va)
{
	pf->var.integer = (int)va_arg(va, intmax_t);
}

void	ft_gtvar_signed_char(t_pf *pf, va_list va)
{
	pf->var.integer = (signed char)va_arg(va, intmax_t);
}

void	ft_gtvar_short_int(t_pf *pf, va_list va)
{
	pf->var.integer = (short)va_arg(va, intmax_t);
}

void	ft_gtvar_size_t(t_pf *pf, va_list va)
{
	pf->var.integer = (size_t)va_arg(va, intmax_t);
}

void	ft_gtvar_long_int(t_pf *pf, va_list va)
{
	pf->var.integer = (long int)va_arg(va, intmax_t);
}
