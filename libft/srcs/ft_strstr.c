/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:50:17 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/06 19:50:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int point;

	i = 0;
	while (haystack[i])
	{
		point = i;
		j = 0;
		while (needle[j] == haystack[i] && needle[j])
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
