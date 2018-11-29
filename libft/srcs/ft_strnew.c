/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:49:42 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 15:54:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*res;
	size_t	i;

	res = (char *)(ft_memalloc(size + 1));
	if (res == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < size + 1)
		{
			res[i] = '\0';
			i++;
		}
	}
	return (res);
}
