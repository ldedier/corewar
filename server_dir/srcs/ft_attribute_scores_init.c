/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attribute_scores_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:46:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/15 15:19:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		fight_cores(t_player *player1, t_player *player2, t_player **winner)
{
	(void)player2;
	*winner = player1;
	return (0);
}

int		ft_blood_bath(t_server *server)
{
	t_list		*ptr;
	t_player	*player1;
	t_player	*player2;
	t_player	*winner;
	t_list		*next;

	ptr = server->players;
	while (ptr != NULL)
	{
		player1 = (t_player *)ptr->content;
		next = ptr->next;
		while (next != NULL)
		{
			player2 = (t_player *)next->content;
			if (fight_cores(player1, player2, &winner))
				return (1);
			winner->nb_victories++;
			if (ft_add_to_list_ptr(&winner->beaten_players,
					player1 == winner ? player2 : player1, sizeof(t_player)))
				return (1);
			next = next->next;
		}
		ptr = ptr->next;
	}
	return (0);
}

int		add_to_score(t_player *beaten_player)
{
	return (1 + beaten_player->nb_victories);
}

int		ft_attribute_scores_init(t_server *server)
{
	t_list		*ptr;
	t_list		*beaten_ptr;
	t_player	*beaten;
	t_player	*player;

	if (ft_blood_bath(server))
		return (1);
	ptr = server->players;
	while (ptr != NULL)
	{
		player = (t_player *)ptr->content;
		beaten_ptr = player->beaten_players;
		while (beaten_ptr != NULL)
		{
			beaten = (t_player *)beaten_ptr->content;
			player->score += add_to_score(beaten);
			beaten_ptr = beaten_ptr->next;
		}
		ptr = ptr->next;
	}
	return (0);
}
