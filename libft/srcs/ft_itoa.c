/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:35:33 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/06 18:39:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_update_len(int nbr, int *len)
{
	unsigned int n;

	if (nbr >= 0)
		n = nbr;
	else
	{
		*len = *len + 1;
		n = -nbr;
	}
	if (n / 10 == 0)
		*len = *len + 1;
	else
	{
		*len = *len + 1;
		ft_update_len(n / 10, len);
	}
}

static void	ft_process_itoa(char *res, int nbr, int length)
{
	unsigned int n;

	if (nbr >= 0)
		n = nbr;
	else
	{
		res[0] = '-';
		n = -nbr;
	}
	if (n / 10 == 0)
	{
		res[length - 1] = n % 10 + '0';
	}
	else
	{
		res[length - 1] = n % 10 + '0';
		ft_process_itoa(res, n / 10, length - 1);
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		length;

	length = 0;
	ft_update_len(n, &length);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (res == NULL)
		return (NULL);
	ft_process_itoa(res, n, length);
	res[length] = '\0';
	return (res);
}
