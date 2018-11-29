/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 01:04:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 04:25:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pf_func g_pf_arr[NB_CHARS] =
{
	['d'] = ft_pf_d,
	['D'] = ft_pf_d_maj,
	['i'] = ft_pf_d,
	['s'] = ft_pf_s,
	['S'] = ft_pf_s_maj,
	['x'] = ft_pf_x,
	['X'] = ft_pf_x_maj,
	['o'] = ft_pf_o,
	['O'] = ft_pf_o_maj,
	['c'] = ft_pf_c,
	['C'] = ft_pf_c_maj,
	['u'] = ft_pf_u,
	['U'] = ft_pf_u_maj,
	['p'] = ft_pf_p,
	['0'] = ft_pf_0,
	['1'] = ft_pf_digit,
	['2'] = ft_pf_digit,
	['3'] = ft_pf_digit,
	['4'] = ft_pf_digit,
	['5'] = ft_pf_digit,
	['6'] = ft_pf_digit,
	['7'] = ft_pf_digit,
	['8'] = ft_pf_digit,
	['9'] = ft_pf_digit,
	['.'] = ft_pf_point,
	['-'] = ft_pf_minus,
	[' '] = ft_pf_space,
	['+'] = ft_pf_plus,
	['#'] = ft_pf_hashtag,
	['%'] = ft_pf_percent,
	['h'] = ft_pf_h,
	['l'] = ft_pf_l,
	['j'] = ft_pf_j,
	['z'] = ft_pf_z,
	['*'] = ft_pf_star,
	['f'] = ft_pf_f,
	['F'] = ft_pf_f,
	['r'] = ft_pf_r,
	['b'] = ft_pf_b,
	['n'] = ft_pf_n
};

int		ft_display_error(t_pf *pf)
{
	int display;

	ft_reset_return();
	display = 1;
	ft_get_buffer("", 0, &display, pf);
	return (-1);
}

/*
** do not empty buffer (line 89) for +70% speed in comparison to real printf
*/

int		ft_process_percent(const char *format, int *i, t_pf *pf, va_list va)
{
	int display;

	*i += 1;
	display = 0;
	while (format[*i] != '\0' && display == 0)
	{
		if (g_pf_arr[(int)(format[*i])] == NULL)
			display = ft_pf_nothing(pf, va, format[*i]);
		else
			display = g_pf_arr[(int)(format[*i])](pf, va, format[*i]);
		if (display == -1)
			return (ft_display_error(pf));
		*i += 1;
	}
	if (ft_may_error_next_conv(format, *i))
		ft_empty_buffer(pf);
	ft_init_pf(pf);
	return (0);
}

int		ft_dvprintf(int fd, const char *format, va_list va)
{
	t_pf		pf;
	int			i;

	pf.fd = fd;
	ft_init_pf(&pf);
	pf.sprintf = 0;
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
	return (ft_reset_return());
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	static int	broken = 0;
	int			ret;
	va_list		va;

	va_start(va, format);
	if ((ret = ft_dvprintf(fd, format, va)) == -1)
		broken = 1;
	va_end(va);
	if (broken)
		return (-1);
	else
		return (ret);
}
