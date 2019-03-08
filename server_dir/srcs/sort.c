/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:27:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 19:35:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			ft_sort_score(void *p1, void *p2)
{
	t_player	*player1;
	t_player	*player2;
	int			ret;

	player1 = (t_player *)p1;
	player2 = (t_player *)p2;
	if ((ret = player2->score - player1->score))
		return (ret);
	return (ft_strcmp_no_case(player1->name, player2->name));
}

void		ft_sort_server(t_server *server)
{
	ft_lst_mergesort(&server->players, ft_sort_score, 0);
}
