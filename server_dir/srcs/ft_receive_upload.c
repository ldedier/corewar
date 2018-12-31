/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receive_upload.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 22:57:11 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/31 16:16:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_send_flag(t_server *server, int client_index, t_flag flag)
{
	char *data;

	if (!(data = malloc(sizeof(t_flag))))
		return (1);
	ft_memcpy(data, &flag, sizeof(t_flag));
	if (ft_send_protected(server->client_sockets[client_index].socket,
				data, sizeof(t_flag)))
		return (1);
	return (0);
}

int		ft_add_player_persistency(t_player *player)
{
	int fd;

	char *filename;
	if (!(filename = ft_strjoin_3(PATH"/cores/", player->name, ".cor")))
		return (1);
	ft_printf("%s\n", filename);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		perror(filename);
		free(filename);
		return (1);
	}
	write(fd, player->bin, player->file_len);
	free(filename);
	close(fd);
	return (0);
}

int		ft_process_send_new_player_to_all(t_server *server, t_player *player)
{
	int			i;
	char		*data;
	int			size;

	i = 0;
	size = sizeof(t_flag) + ft_get_player_size_all(player);
	if (!(data = malloc(size)))
		return (1);
	server->flag = FLAG_NEW_CORE;
	i += ft_memcpy_ret(&(data[i]), &server->flag, sizeof(t_flag));
	i += ft_memcpy_ret(&(data[i]), &player->score, sizeof(t_score));
	i += ft_memcpy_ret(&(data[i]), &player->name_len, sizeof(t_name_len));
	i += ft_memcpy_ret(&(data[i]), &player->name, player->name_len);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!server->client_sockets[i].isfree)
		{
			if (ft_send_protected(server->client_sockets[i].socket,
					data, size))
				return (1);
		}
		i++;
	}
	return (0);
}

int		ft_receive_upload(t_server *server, int client_index, int nb_bytes)
{
	t_player	*player;
	int			i;
	int			ret;

	ft_printf("%d\n", nb_bytes);
	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (1);
	if (nb_bytes < (int)(sizeof(t_flag) + sizeof(t_file_len)))
		return (1);
	i = sizeof(t_flag);
	ft_memcpy_recv(&player->file_len, server->buffer, &i, sizeof(t_file_len));
	if (nb_bytes < (int)(i + player->file_len))
		return (1);
	if (player->file_len >= TOT_SIZE)
		return (1);
	ret = ft_process_read_player(&(server->buffer[i]), player->file_len, player);
	if (ret)
		return (1);
	else
	{
		if (get_player(server, player->name))
			return (ft_send_flag(server, client_index, UPLOAD_NAME_TAKEN));
		else
		{
			//ft_process_player_score(server, player);
			ft_process_send_new_player_to_all(server, player);
			if (ft_add_to_list_ptr_back(&(server->players), player, sizeof(t_player)))
				return (1);
			ft_add_player_persistency(player);
		}
	}
	return (0);
}
