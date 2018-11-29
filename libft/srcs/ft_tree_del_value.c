/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_del_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:15:33 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/27 22:16:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_del_value(t_tree **tree)
{
	if (*tree)
	{
		ft_tree_del_value(&((*tree)->left));
		ft_tree_del_value(&((*tree)->right));
		free((*tree)->content);
		free(*tree);
	}
}
