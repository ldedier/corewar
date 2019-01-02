/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_player_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 18:00:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/02 18:47:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int     ft_write_to_downloads(t_player *player)
{
	int fd;

	char *filename;
	if (!(filename = ft_strjoin_3(PATH"/Downloads/", player->name, ".cor")))
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

int		ft_process_player_bin_info(t_vm *vm, int nb_bytes)
{
	int			i;
	t_flag		flag;
	t_player	*player;
	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (1);
	i = 0;
	(void)nb_bytes;
	ft_memcpy_recv(&flag, vm->client.buffer, &i, sizeof(t_flag));
	if (flag != GET_CORE_BIN)
		return (1);
	ft_memcpy_recv(&player->file_len, vm->client.buffer,
			&i, sizeof(t_file_len));
	ft_memcpy(&player->bin, &(vm->client.buffer[i]), player->file_len);
	if (ft_process_read_player(&(vm->client.buffer[i]),
		player->file_len, player))
		return (1);
	if (ft_write_to_downloads(player))
		return (1);
	if (ft_add_to_list_ptr_back(&vm->visu.downloaded_players, player,
			sizeof(t_player)))
		return (1);
	player->num = vm->nb;
	player->from_server = 1;
	ft_update_vscrollbar_downloads_compressed_size(vm, &(vm->visu));
	return (0);
}

int		ft_receive_player_bin_info(t_vm *vm)
{
	int nb_bytes;

	if (SDLNet_CheckSockets(vm->client.socket_set, 1500))
	{
		if (SDLNet_SocketReady(vm->client.socket))
		{
			if ((nb_bytes = SDLNet_TCP_Recv(vm->client.socket, vm->client.buffer,
							MAX_TCP_PACKET)) <= 0)
				return (ft_net_error());
			else
				return (ft_process_player_bin_info(vm, nb_bytes));
		}
		else
			return (ft_net_error());
	}
	else
	{
		ft_printf("no response for server for too long\n");
		return (1);
	}
}

int     ft_query_player_bin(t_vm *vm, t_client_slot *cs)
{
	int		total_size;
	int		size;
	char	*data;

	total_size = ft_query_player_size(cs->player);
	if (!(data = (char *)malloc(total_size)))
		return (1);
	vm->client.flag = GET_CORE_BIN;
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &(vm->client.flag), sizeof(t_flag));
	size += ft_memcpy_ret(&(data[size]), &(cs->player->name_len), sizeof(t_name_len));
	size += ft_memcpy_ret(&(data[size]), &(cs->player->name), cs->player->name_len);
	if (ft_send_protected(vm->client.socket, data, size))
		return (1);
	return (ft_receive_player_bin_info(vm));
}
