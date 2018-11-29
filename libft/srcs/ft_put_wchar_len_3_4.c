/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_wchar_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:19:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:18:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_len_3_1(unsigned char str[4], int value)
{
	if (value <= 4095)
	{
		str[0] = 224;
		str[1] = 160 | ((value >> 6) & 31);
		str[2] = 128 | (value & 63);
	}
	else if (value <= 8191)
	{
		str[0] = 225;
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
	else if (value <= 16383)
	{
		str[0] = 226 | ((value >> 12) & 1);
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
	else
	{
		str[0] = 228 | ((value >> 12) & 3);
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
}

void	ft_len_3_2(unsigned char str[4], int value)
{
	if (value <= 49151)
	{
		str[0] = 232 | ((value >> 12) & 3);
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
	else if (value <= 53247)
	{
		str[0] = 236;
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
	else if (value <= 55295)
	{
		str[0] = 237;
		str[1] = 128 | ((value >> 6) & 31);
		str[2] = 128 | (value & 63);
	}
	else
	{
		str[0] = 238 | ((value >> 12) & 1);
		str[1] = 128 | ((value >> 6) & 63);
		str[2] = 128 | (value & 63);
	}
}

void	ft_3_bytes_len(unsigned char str[4], int value)
{
	if (value <= 32767)
		ft_len_3_1(str, value);
	else
		ft_len_3_2(str, value);
}

void	ft_len_4_1(unsigned char str[4], int value)
{
	if (value <= 131071)
	{
		str[0] = 240;
		str[1] = 144 | ((value >> 12) & 15);
		str[2] = 128 | ((value >> 6) & 63);
		str[3] = 128 | (value & 63);
	}
	else if (value <= 262143)
	{
		str[0] = 240;
		str[1] = 160 | ((value >> 12) & 31);
		str[2] = 128 | ((value >> 6) & 63);
		str[3] = 128 | (value & 63);
	}
	else
	{
		str[0] = 241;
		str[1] = 128 | ((value >> 12) & 63);
		str[2] = 128 | ((value >> 6) & 63);
		str[3] = 128 | (value & 63);
	}
}

void	ft_4_bytes_len(unsigned char str[4], int value)
{
	if (value <= 524287)
		ft_len_4_1(str, value);
	else if (value <= 1048575)
	{
		str[0] = 242 | ((value >> 18) & 1);
		str[1] = 128 | ((value >> 12) & 63);
		str[2] = 128 | ((value >> 6) & 63);
		str[3] = 128 | (value & 63);
	}
	else
	{
		str[0] = 244;
		str[1] = 128 | ((value >> 12) & 15);
		str[2] = 128 | ((value >> 6) & 63);
		str[3] = 128 | (value & 63);
	}
}
