/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_list_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:29:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/29 17:47:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_add_to_list_ptr(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew_ptr(content, size)))
		return (1);
	else
		ft_lstadd(list, node);
	return (0);
}
