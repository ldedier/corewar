/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:48:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 22:02:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_get_player_size_all(t_player *player)
{
	int size;

	size = 0;
	size += sizeof(t_score);
	size += sizeof(t_name_len);
	size += player->name_len;
	return (size);
}

int		ft_get_data_size_all(t_server *server)
{
	int		size;
	t_list	*ptr;
	t_player *player;

	size = 0;
	size += sizeof(t_flag);
	size += sizeof(t_nb_players);
	ptr = server->players;
	while (ptr != NULL)
	{
		player = (t_player *)(ptr->content);
		size += ft_get_player_size_all(player);
		ptr = ptr->next;
	}
	return (size);
}

void	ft_add_player_data_all(void *content_player, char *data, int *size)
{
	t_player		*player;

	player = (t_player *)content_player;
	*size += ft_memcpy_ret(&(data[*size]), &(player->score), sizeof(player->score));
	*size += ft_memcpy_ret(&(data[*size]), &(player->name_len), sizeof(t_name_len));
	*size += ft_memcpy_ret(&(data[*size]), player->name, player->name_len);
}

int		ft_send_all_cores(TCPsocket socket, t_server *server)
{
	char			*data;
	t_nb_players	nb_players;
	int				total_size;
	int				size;
	t_list			*ptr;

	server->flag = GET_LIST;
	total_size = ft_get_data_size_all(server);
	nb_players = ft_lstlength(server->players);
	if (!(data = (char *)(malloc(total_size))))
		return (1);
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &(server->flag), sizeof(server->flag));
	size += ft_memcpy_ret(&(data[size]), &(nb_players), sizeof(nb_players));
	ptr = server->players;
	while (ptr != NULL)
	{
		ft_add_player_data_all(ptr->content, data, &size);
		ptr = ptr->next;
	}
	if (ft_send_protected(socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}
