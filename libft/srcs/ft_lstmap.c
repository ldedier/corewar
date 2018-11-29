/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:42:20 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 18:44:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *ptr;

	res = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		ft_lstpushback(&res, f(ptr));
		ptr = ptr->next;
	}
	return (res);
}
