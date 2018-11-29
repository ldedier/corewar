/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:55:14 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 20:18:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlength(t_list *list)
{
	int length;

	length = 0;
	while (list != NULL)
	{
		length++;
		list = list->next;
	}
	return (length);
}
