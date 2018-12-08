/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_c_maj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:37:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 18:10:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putwstr(int *data, t_pf *pf)
{
	int i;

	i = 0;
	while (data[i])
	{
		ft_put_wchar(data[i], pf);
		i++;
	}
}

void	ft_putwnstr(int *data, int precision, t_pf *pf)
{
	int i;
	int bytes_wrote;
	int len_towrite;

	bytes_wrote = 0;
	i = 0;
	while (data[i] && bytes_wrote < precision)
	{
		len_towrite = ft_wchar_len(data[i]);
		if (bytes_wrote + len_towrite <= precision)
		{
			ft_put_wchar(data[i], pf);
			bytes_wrote += len_towrite;
		}
		else
			bytes_wrote += precision;
		i++;
	}
}

int		ft_pf_c_maj(t_pf *pf, va_list va, char c)
{
	int len;

	(void)c;
	pf->var.integer = va_arg(va, int);
	if ((len = ft_wchar_len(pf->var.integer)) == -1 ||
			(len > MB_CUR_MAX && pf->var.integer >= 255))
		return (-1);
	ft_add_padding_pre(pf, len);
	ft_put_wchar(pf->var.integer, pf);
	ft_add_padding_post(pf, len);
	return (1);
}
