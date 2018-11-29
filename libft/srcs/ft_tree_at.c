/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:09:25 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/29 14:43:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_tree_at_infix_process(t_tree *tree, int *index)
{
	void	*res;

	if (tree != NULL)
	{
		if ((res = ft_tree_at_infix_process(tree->left, index)))
			return (res);
		if (*index == 0)
			return (tree->content);
		*index -= 1;
		if ((res = ft_tree_at_infix_process(tree->right, index)))
			return (res);
	}
	return (NULL);
}

void		*ft_tree_at_infix(t_tree *tree, int index)
{
	return (ft_tree_at_infix_process(tree, &index));
}
