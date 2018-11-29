/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:08:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/02 03:25:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **lst, t_list *toadd)
{
	t_list *ptr;

	ptr = *lst;
	if (*lst == NULL)
		*lst = toadd;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = toadd;
	}
}
