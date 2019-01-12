/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:48:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/12 10:22:40 by ldedier          ###   ########.fr       */
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

char	*ft_get_buffer_all_cores(t_server *server, t_flag flag, int *size)
{
	char			*data;
	t_nb_players	nb_players;
	int				total_size;
	t_list			*ptr;

	server->flag = flag;
	total_size = ft_get_data_size_all(server);
	nb_players = ft_lstlength(server->players);
	if (!(data = (char *)(malloc(total_size))))
		return (NULL);
	*size = 0;
	*size += ft_memcpy_ret(&(data[*size]), &(server->flag), sizeof(server->flag));
	*size += ft_memcpy_ret(&(data[*size]), &(nb_players), sizeof(nb_players));
	ptr = server->players;
	while (ptr != NULL)
	{
		ft_add_player_data_all(ptr->content, data, size);
		ptr = ptr->next;
	}
	return (data);
}

int		ft_send_all_cores(TCPsocket socket, t_server *server, t_flag flag)
{
	char			*data;
	int				size;

	if (!(data = ft_get_buffer_all_cores(server, flag, &size)))
		return (1);
	if (ft_send_protected(socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}
