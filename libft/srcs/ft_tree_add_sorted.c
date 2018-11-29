/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:09:23 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/27 20:11:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tree_add_sorted(t_tree **tree, void *content,
			int (*sort)(void*, void *))
{
	if (*tree == NULL)
	{
		if (!(*tree = ft_tree_new_ptr(content)))
			return (1);
		else
			return (0);
	}
	else
	{
		if (sort((*tree)->content, content) > 0)
			return (ft_tree_add_sorted(&((*tree)->left), content, sort));
		else
			return (ft_tree_add_sorted(&((*tree)->right), content, sort));
	}
}
