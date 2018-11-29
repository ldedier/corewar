/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:55:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/22 17:44:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_split_lst_half(t_list *lst, t_list **first_half,
				t_list **second_half)
{
	t_list	*slow;
	t_list	*twice_as_fast;

	slow = lst;
	twice_as_fast = lst->next;
	while (twice_as_fast)
	{
		twice_as_fast = twice_as_fast->next;
		if (twice_as_fast)
		{
			twice_as_fast = twice_as_fast->next;
			slow = slow->next;
		}
	}
	*first_half = lst;
	*second_half = slow->next;
	slow->next = NULL;
}

static t_list	*ft_merge_sorted_lists(t_list *first, t_list *second,
					int (*sort)(void *, void *), int rev)
{
	t_list *res;

	if (!first)
		return (second);
	else if (!second)
		return (first);
	if (rev == 0 ? sort(first->content, second->content) < 0 :
			sort(first->content, second->content) > 0)
	{
		res = first;
		res->next = ft_merge_sorted_lists(first->next, second, sort, rev);
	}
	else
	{
		res = second;
		res->next = ft_merge_sorted_lists(first, second->next, sort, rev);
	}
	return (res);
}

void			ft_lst_mergesort(t_list **list,
		int (*sort)(void *, void *), int rev)
{
	t_list *ptr;
	t_list *first_half;
	t_list *second_half;

	ptr = *list;
	if (!ptr || !(ptr->next))
		return ;
	ft_split_lst_half(ptr, &first_half, &second_half);
	ft_lst_mergesort(&first_half, sort, rev);
	ft_lst_mergesort(&second_half, sort, rev);
	*list = ft_merge_sorted_lists(first_half, second_half, sort, rev);
}
