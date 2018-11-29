/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:46:31 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/12 13:55:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	to_cpy;

	i = 0;
	while (i < n)
	{
		to_cpy = (unsigned char)*(char *)(src + i);
		*(char *)(dest + i) = to_cpy;
		i++;
		if (to_cpy == (unsigned char)c)
			return (dest + i);
	}
	return (NULL);
}
