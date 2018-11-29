/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:21:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 19:51:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_delete_node(t_list **prev, t_list **ptr, t_list **list)
{
	if (*prev == NULL)
		*list = (*ptr)->next;
	else
		(*prev)->next = (*ptr)->next;
	free((*ptr)->content);
	free(*ptr);
	return (0);
}
