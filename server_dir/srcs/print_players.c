/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 19:37:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		print_player(int number, t_player *player)
{
	t_list		*ptr;
	t_player	*bplayer;

	ft_printf("%s%s%sPlayer #%d: %s%s", BOLD, UNDERLINE, RED, number,
			player->name, EOC);
	ft_printf("\n%sscore: %d %s(with %s%d%s beaten players)\n", YELLOW,
			player->score, EOC, GREEN, player->nb_victories, EOC);
	ptr = player->beaten_players;
	while (ptr)
	{
		bplayer = (t_player *)(ptr->content);
		ft_printf("\t\t%s%s (%d beaten players => + %d)%s\n", BLUE,
			bplayer->name, bplayer->nb_victories,
				bplayer->nb_victories + 1, EOC);
		ptr = ptr->next;
	}
}

void			print_players(t_list *players)
{
	t_list	*ptr;
	int		i;

	i = 0;
	ft_printf("\n\n%s--ARENA RESULTS--%s%s\n\n", RED, UNDERLINE, EOC);
	ptr = players;
	while (ptr)
	{
		print_player(++i, (t_player *)ptr->content);
		ptr = ptr->next;
	}
}
