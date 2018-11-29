/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_del_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:16:04 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/27 22:17:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_del_ptr(t_tree **tree)
{
	if (*tree)
	{
		ft_tree_del_ptr(&((*tree)->left));
		ft_tree_del_ptr(&((*tree)->right));
		free(*tree);
	}
}
