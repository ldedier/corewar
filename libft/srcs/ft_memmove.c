/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:50:09 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/06 18:50:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	size_t i;

	i = 0;
	if (dest < src)
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	else
		while (i < n)
		{
			*(char *)(dest + n - i - 1) = *(char *)(src + n - i - 1);
			i++;
		}
	return (dest);
}
