/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_postfix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:57:56 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 21:19:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_postfix(t_tree *tree, void (*f)(t_tree *))
{
	if (tree != NULL)
	{
		ft_postfix(tree->left, f);
		ft_postfix(tree->right, f);
		f(tree);
	}
}
