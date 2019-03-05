/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:41:42 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/05 13:46:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

/*
** parse_name_and_comm static function is used by the parse function to save
** the name and the comment of given files into their respective arrays in each
** player's structure: player[x].name and player[x].comm
*/

static void		parse_name_and_comm(t_player *player)
{
	int		n;

	n = 0;
	while (n < PROG_NAME_LENGTH)
	{
		player->name[n] = player->bin[n + 4];
		n++;
	}
	player->name[n] = 0;
	n = 0;
	while (n < COMMENT_LENGTH)
	{
		player->comm[n] = player->bin[n + 12 + PROG_NAME_LENGTH];
		n++;
	}
	player->comm[n] = 0;
}

/*
** check_head_size static function is used to check the size given in the .cor's
** header. If it doesn't match the actual size of the instructions, it exits
** the program.
*/

static void		check_head_size(t_player *player)
{
	char	size[4];
	int		n;

	n = 0;
	while (n < 4)
	{
		size[3 - n] = player->bin[PROG_NAME_LENGTH + 8 + n];
		n++;
	}
	player->header_size = *(int *)size;
}

/*
** parse_instructions static function is used by the parse function to add
** the [algo] part (the instructions) inside the player structure. It also
** checks if the instructions part exceeds the max allowed size CHAMP_MAX_SIZE.
*/

static int		parse_instructions(t_player *player)
{
	int		n;
	int		l;

	n = 0;
	while ((l = PROG_NAME_LENGTH + 16 + COMMENT_LENGTH + n) < player->file_len)
	{
		player->algo[n] = player->bin[l];
		n++;
	}
	player->algo_len = n;
	check_head_size(player);
	if (n != player->header_size)
		return (ft_return_verbosed(WRG_HEAD_SIZE, 1));
	if (n > CHAMP_MAX_SIZE)
		return (ft_return_verbosed(MAX_CHAMP, 1));
	while (n < CHAMP_MAX_SIZE)
	{
		player->algo[n] = 0;
		n++;
	}
	return (0);
}

/*
** parse function tries to parse each player's binary data to retrieve their
** information, i.e the [name], which is the name of the champion, the [comm],
** containing the commentary, and the [algo] containing the instructions.
*/

int				ft_parse_player(t_player *player)
{
	parse_name_and_comm(player);
	if (parse_instructions(player))
		return (1);
	player->name_len = ft_strlen(player->name);
	player->comm_len = ft_strlen(player->comm);
	player->score = 0;
	player->relevant = 1;
	player->color.value = 1;
	player->from_server = 0;
	player->beaten_players = NULL;
	player->nb_victories = 0;
	player->live = 0;
	player->last_live_cycle = 0;
	return (0);
}
