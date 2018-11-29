/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:13:27 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 22:52:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_get_val g_arr_getval_std[7] =
{
	ft_gtvar_none,
	ft_gtvar_signed_char,
	ft_gtvar_short_int,
	ft_gtvar_size_t,
	ft_gtvar_long_int,
	ft_gtvar_long_long_int,
	ft_gtvar_intmax_t
};

static t_get_val g_arr_getval_u[7] =
{
	ft_gtvar_uint,
	ft_gtvar_uchar,
	ft_gtvar_ushort_int,
	ft_gtvar_size_t,
	ft_gtvar_ulint,
	ft_gtvar_ullint,
	ft_gtvar_uintmax_t
};

static t_get_val g_arr_getval_ul[7] =
{
	ft_gtvar_ulint,
	ft_gtvar_uchar,
	ft_gtvar_ulint,
	ft_gtvar_size_t,
	ft_gtvar_ulint,
	ft_gtvar_ullint,
	ft_gtvar_uintmax_t
};

void	get_casted_value(t_pf *pf, va_list va)
{
	g_arr_getval_std[pf->flags.length_mod](pf, va);
}

void	get_casted_value_unsigned(t_pf *pf, va_list va)
{
	g_arr_getval_u[pf->flags.length_mod](pf, va);
}

void	get_casted_value_unsigned_maj(t_pf *pf, va_list va)
{
	g_arr_getval_ul[pf->flags.length_mod](pf, va);
}
