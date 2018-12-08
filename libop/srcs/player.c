/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:56:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 14:56:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_player *ft_new_player(char *name, t_name_len name_len, t_score score)
{
	t_player *res;

	if (!(res = (t_player *)(malloc(sizeof(t_player)))))
		return (NULL);
	ft_memcpy(res->name, name, name_len);
	res->name[name_len] = '\0';
	res->score = score;
	return (res);
}

void	ft_print_player(t_player *player)
{
	ft_printf("%s\n", player->name);
	ft_printf("%d\n\n", player->score);
}

void	ft_print_players(t_list *players)
{
	t_list		*ptr;
	t_player	*player;

	ptr = players;
	while (ptr != NULL)
	{
		player = (t_player *)(ptr->content);
		ft_print_player(player);
		ptr = ptr->next;
	}
}
