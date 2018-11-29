/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:45:07 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/08 15:21:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*res;
	size_t	i;

	res = malloc(size);
	if (res == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < size)
		{
			*(char *)(res + i) = 0;
			i++;
		}
		return (res);
	}
}
