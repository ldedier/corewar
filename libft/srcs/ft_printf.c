/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 01:04:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:46:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *restrict format, ...)
{
	static int	broken = 0;
	int			ret;
	va_list		va;

	va_start(va, format);
	if ((ret = ft_dvprintf(1, format, va)) == -1)
		broken = 1;
	va_end(va);
	if (broken)
		return (-1);
	else
		return (ret);
}
