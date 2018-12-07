/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 22:05:47 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 22:31:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"

t_core  *ft_new_core(char *name, t_score score)
{
	t_core *res;

	if (!(res = malloc(sizeof(t_core))))
		return (NULL);
	res->code.size = 0;
	res->score = score;
	res->name = name;
	return (res);
}

void	ft_print_core(t_core *core)
{
	ft_printf("name: %s\n", core->name);
	ft_printf("score: %d\n\n", core->score);
}

void	ft_print_cores(t_list *cores)
{
	t_list *ptr;
	t_core *core;

	ptr = cores;
	while (ptr != NULL)
	{
		core = ptr->content;
		ft_print_core(core);	
		ptr = ptr->next;
	}
}
