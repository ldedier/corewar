/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_list_ptr_back.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:29:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 22:20:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_add_to_list_ptr_back(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew_ptr(content, size)))
		return (1);
	else
		ft_lstpushback(list, node);
	return (0);
}
