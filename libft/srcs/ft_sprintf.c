/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:38:11 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 10:52:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_svprintf(char *buffer, const char *format, va_list va)
{
	t_pf		pf;
	int			i;

	pf.buffer = buffer;
	ft_init_pf(&pf);
	pf.sprintf = 1;
	i = 0;
	while (format[i] != '\0')
	{
		while (format[i] != '\0' && format[i] != '%')
		{
			ft_putchar_buff(format[i], &pf);
			i++;
		}
		if (format[i] == '%')
		{
			if (ft_process_percent(format, &i, &pf, va) == -1)
				return (-1);
		}
	}
	ft_empty_buffer(&pf);
	pf.buffer[ft_add_return(0)] = '\0';
	return (ft_reset_return());
}

int		ft_sprintf(char *buffer, const char *restrict format, ...)
{
	static int	broken = 0;
	int			ret;
	va_list		va;

	va_start(va, format);
	if ((ret = ft_svprintf(buffer, format, va)) == -1)
		broken = 1;
	va_end(va);
	if (broken)
		return (-1);
	else
		return (ret);
}
