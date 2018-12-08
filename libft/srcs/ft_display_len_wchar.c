/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_len_wchar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 23:43:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 18:11:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_is_forbidden_value(int nb)
{
	if (nb < 0)
		return (-1);
	if (nb >= 55296 && nb <= 57343)
		return (1);
	return (0);
}

int		ft_wchar_len(int nb)
{
	if (ft_is_forbidden_value(nb))
		return (-1);
	else if (nb < 0)
		return (-1);
	else if (nb <= 127 || (nb <= 255 && MB_CUR_MAX < 2))
		return (1);
	else if (nb <= 2047)
		return (2);
	else if (nb <= 65535)
		return (3);
	else if (nb <= 1114111)
		return (4);
	else
		return (-1);
}

int		ft_has_forbidden_values(t_pf pf)
{
	int i;
	int len;
	int *data;
	int res;

	i = 0;
	res = 0;
	data = pf.var.wstr;
	while (data[i] && (res < pf.flags.precision || !pf.precised_precision))
	{
		if ((len = ft_wchar_len(data[i])) == -1)
			return (1);
		if (len > MB_CUR_MAX)
			return (1);
		res += ft_wchar_len(data[i]);
		i++;
	}
	return (0);
}

int		ft_wstrlen(int *data)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (data[i])
	{
		res += ft_wchar_len(data[i]);
		i++;
	}
	return (res);
}

int		ft_wstrlen_prec(int *data, int precision)
{
	int i;
	int bytes_to_write;
	int len_towrite;

	bytes_to_write = 0;
	i = 0;
	while (data[i] && bytes_to_write < precision)
	{
		len_towrite = ft_wchar_len(data[i]);
		if (bytes_to_write + len_towrite <= precision)
			bytes_to_write += len_towrite;
		else
			return (bytes_to_write);
		i++;
	}
	return (bytes_to_write);
}
