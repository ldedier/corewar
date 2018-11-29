/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:23:21 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 15:45:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;
	int j;
	int point;

	i = 0;
	while (haystack[i] && i < (int)len)
	{
		point = i;
		j = 0;
		while (needle[j] == haystack[i] && needle[j] && i < (int)len)
		{
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return (char *)(&(haystack[point]));
		i = point + 1;
	}
	if (needle[0] == '\0')
		return ((char *)(&(haystack[i])));
	else
		return (NULL);
}
