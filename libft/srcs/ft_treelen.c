/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:16:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/29 14:43:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_treelen(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	else
		return (1 + ft_treelen(tree->left) + ft_treelen(tree->right));
}
