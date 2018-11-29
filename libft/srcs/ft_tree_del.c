/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:25:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/27 20:31:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_del(t_tree **tree, void (*free_func)(void *))
{
	if (*tree)
	{
		ft_tree_del(&((*tree)->left), free_func);
		ft_tree_del(&((*tree)->right), free_func);
		free_func((*tree)->content);
		free(*tree);
	}
}
