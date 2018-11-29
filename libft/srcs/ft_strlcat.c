/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:45:06 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/06 19:46:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	int res;
	int i;
	int j;

	res = min(size, ft_strlen(dest)) + ft_strlen(src);
	if (size == 0)
		return (res);
	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j] && (size_t)(i + j) < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (res);
}
