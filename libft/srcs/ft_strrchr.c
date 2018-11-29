/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:11:12 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 15:22:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int i;
	int point;

	point = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			point = i;
		i++;
	}
	if (point == -1)
		if (c == '\0')
			return ((char *)(&(s[i])));
		else
			return (NULL);
	else
		return (char *)(&(s[point]));
}
