/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:58:48 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 21:18:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_prefix(t_tree *tree, void (*f)(t_tree *))
{
	if (tree != NULL)
	{
		f(tree);
		ft_prefix(tree->left, f);
		ft_prefix(tree->right, f);
	}
}
