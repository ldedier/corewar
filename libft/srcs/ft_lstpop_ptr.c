/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:34:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/15 16:34:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop_ptr(t_list **list)
{
	void	*content;
	t_list	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		*list = (*list)->next;
		free(ptr);
		return (content);
	}
	return (NULL);
}
