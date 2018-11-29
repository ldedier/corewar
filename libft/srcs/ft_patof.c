/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 00:52:28 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/14 18:32:05 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	getinteg(char **str)
{
	int	num;

	num = ft_patoi(str);
	num *= ft_onesign(num);
	return ((double)num);
}

static double	getmant(char **str, int *scss)
{
	int		mant;
	int		digits;
	double	mul;

	digits = 0;
	while (ft_isdigit((*str)[digits]))
		digits++;
	mant = ft_patoi(str);
	if (scss && (**str != ' ' && **str != '\0' && **str != '\n'))
		*scss = 0;
	mul = 1;
	while (digits-- > 0)
		mul /= 10;
	return ((double)mant * mul);
}

double			ft_patof(char **str, int *scss)
{
	int		sign;
	double	res;

	while (ft_isspace(**str))
		(*str)++;
	sign = 1;
	if (**str == '-')
		sign = -1;
	res = getinteg(str);
	if (**str != '.' || !ft_isdigit(*((*str) + 1)))
	{
		if (**str != ' ' && scss)
			*scss = 0;
		return (res * sign);
	}
	(*str)++;
	res = (res + getmant(str, scss)) * sign;
	return (res);
}
