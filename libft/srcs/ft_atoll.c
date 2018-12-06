/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:29:24 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/03 20:49:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoll(const char *str)
{
	int				neg;
	long long int	res;
	int				i;

	neg = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + ((str[i] - '0') % 10);
		i++;
	}
	return (res * neg);
}
