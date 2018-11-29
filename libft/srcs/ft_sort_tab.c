/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:19:15 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/12 14:45:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_tab(int *tab, size_t length)
{
	int changed;
	int i;
	int tmp;

	changed = 1;
	while (changed == 1)
	{
		changed = 0;
		i = 0;
		while ((size_t)i + 1 < length)
		{
			if (tab[i] > tab[i + 1])
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				changed = 1;
			}
			i++;
		}
	}
}
