/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receive_upload.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 22:57:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 19:29:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_add_player_persistency(t_player *player)
{
	int		fd;
	char	*filename;

	if (!(filename = ft_strjoin_3(PATH"/cores/", player->name, ".cor")))
		return (1);
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

int		ft_process_send_new_players_to_all(t_server *server)
{
	int			i;
	char		*data;
	int			size;

	i = 0;
	if (!(data = ft_get_buffer_all_cores(server, FLAG_NEW_CORES, &size)))
		return (1);
	while (i < MAX_CLIENTS)
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

int		ft_process_player_scores(t_server *server, t_player *uploaded_player)
{
	t_list		*ptr;
	t_player	*player;
	int			i;

	ptr = server->players;
	i = 1;
	while (ptr != NULL)
	{
		player = (t_player *)ptr->content;
		if (fight_cores(&server->vm, player, uploaded_player))
			return (1);
		server->vm.winner->nb_victories++;
		if (ft_add_to_list_ptr(&server->vm.winner->beaten_players,
				uploaded_player == server->vm.winner ? player : uploaded_player,
					sizeof(t_player)))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int		ft_process_uploaded_player(t_server *server,
		t_player *player, int client_index)
{
	if (get_player(server, player->name))
	{
		free(player);
		return (ft_send_flag(server, client_index, UPLOAD_NAME_TAKEN));
	}
	else
	{
		ft_process_player_scores(server, player);
		if (ft_add_to_list_ptr_back(&(server->players),
					player, sizeof(t_player)))
			return (1);
		ft_process_score(server);
		ft_process_send_new_players_to_all(server);
		ft_add_player_persistency(player);
		ft_sort_server(server);
	}
	return (0);
}

int		ft_receive_upload(t_server *server, int client_index, int nb_bytes)
{
	t_player	*player;
	int			i;
	int			ret;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (1);
	if (nb_bytes < (int)(sizeof(t_flag) + sizeof(t_file_len)))
		return (1);
	i = sizeof(t_flag);
	ft_memcpy_recv(&player->file_len, server->buffer, &i, sizeof(t_file_len));
	if (nb_bytes < (int)(i + player->file_len))
		return (1);
	if (player->file_len > TOT_SIZE)
		return (1);
	ret = ft_process_read_player(&(server->buffer[i]),
			player->file_len, player);
	if (ret)
		return (1);
	else if (out_of_atlas_range(player->name))
		return (ft_send_flag(server, client_index, UPLOAD_NAME_INVALID));
	else
		return (ft_process_uploaded_player(server, player, client_index));
}
