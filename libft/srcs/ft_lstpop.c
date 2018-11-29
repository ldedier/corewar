/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:34:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/15 16:35:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **list)
{
	void	*content;
	t_list	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		*list = (*list)->next;
		free(ptr);
		free(content);
	}
}
