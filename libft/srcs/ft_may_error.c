/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_may_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 22:22:11 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/08 22:22:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_is_in_str(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_is_conv(char c)
{
	return (ft_is_in_str("dDsScCpoOiuUxXbr", c));
}

int		ft_may_error_next_conv(const char *format, int i)
{
	while (format[i] && format[i] != '%')
		i++;
	if (format[i] == '%')
	{
		i++;
		while (format[i] && !ft_is_conv(format[i]))
			i++;
		if (ft_is_in_str("Cc", format[i]))
			return (1);
	}
	return (0);
}
