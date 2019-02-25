/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attribute_scores_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:46:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 16:27:05 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_blood_bath(t_server *server)
{
	t_list		*ptr;
	t_player	*player1;
	t_player	*player2;
	t_list		*next;
	int			ret;

	ptr = server->players;
	while (ptr != NULL)
	{
		player1 = (t_player *)ptr->content;
		next = ptr->next;
		while (next != NULL)
		{
			ft_printf("while\n");
			player2 = (t_player *)next->content;
			ret = fight_cores(&server->vm, player1, player2);
			ft_printf("ret = %d\n", ret);
			if (ret)
				return (1);
			server->vm.winner->nb_victories++;
			ft_printf("server winner = %s victories = %d\n",
					server->vm.winner->name, server->vm.winner->nb_victories);
			if (ft_add_to_list_ptr(&server->vm.winner->beaten_players,
										player1 == server->vm.winner ?
										player2 : player1, sizeof(t_player)))
			{
				ft_printf("exit blood bath\n");
				return (1);
			}
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

void	ft_process_score(t_server *server)
{
	t_list		*ptr;
	t_list		*beaten_ptr;
	t_player	*beaten;
	t_player	*player;

	ptr = server->players;
	while (ptr != NULL)
	{
		player = (t_player *)ptr->content;
		player->score = 0;
		beaten_ptr = player->beaten_players;
		while (beaten_ptr != NULL)
		{
			beaten = (t_player *)beaten_ptr->content;
			player->score += add_to_score(beaten);
			beaten_ptr = beaten_ptr->next;
		}
		ptr = ptr->next;
	}
}

int		ft_attribute_scores_init(t_server *server)
{
	if (ft_blood_bath(server))
		return (1);
	ft_process_score(server);
	return (0);
}
