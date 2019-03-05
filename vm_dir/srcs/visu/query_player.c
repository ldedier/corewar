/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:47:33 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 19:47:00 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_query_player_size(t_player *player)
{
	int size;

	size = 0;
	size += sizeof(t_flag);
	size += sizeof(t_name_len);
	size += ft_strlen(player->name);
	return (size);
}

int		ft_process_player_info(t_vm *vm, t_client_slot *cs, int nb_bytes)
{
	int			i;
	t_player	*player;
	t_flag		flag;

	player = cs->player;
	(void)nb_bytes;
	i = 0;
	ft_memcpy_recv(&flag, vm->client.buffer, &i, sizeof(t_flag));
	if (flag != GET_CORE)
		return (1);
	ft_memcpy_recv(&player->comm_len, vm->client.buffer,
		&i, sizeof(t_comment_len));
	ft_memcpy_recv(&player->comm, vm->client.buffer, &i, player->comm_len);
	player->comm[player->comm_len] = '\0';
	ft_memcpy_recv(&player->algo_len, vm->client.buffer,
		&i, sizeof(t_code_len));
	ft_memcpy_recv(&player->algo, vm->client.buffer, &i, player->algo_len);
	cs->downloaded = 1;
	return (0);
}

int		ft_receive_player_info(t_vm *vm, t_client_slot *cs)
{
	int nb_bytes;

	if (SDLNet_CheckSockets(vm->client.socket_set, 1500))
	{
		if (SDLNet_SocketReady(vm->client.socket))
		{
			if ((nb_bytes = SDLNet_TCP_Recv(vm->client.socket,
							vm->client.buffer, MAX_TCP_PACKET)) <= 0)
				return (ft_net_error());
			else
				return (ft_process_player_info(vm, cs, nb_bytes));
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

int		ft_query_player(t_vm *vm, t_client_slot *cs)
{
	int		total_size;
	int		size;
	char	*data;

	total_size = ft_query_player_size(cs->player);
	if (!(data = (char *)malloc(total_size)))
		return (1);
	vm->client.flag = GET_CORE;
	size = 0;
	size += ft_memcpy_ret(&(data[size]), &(vm->client.flag), sizeof(t_flag));
	size += ft_memcpy_ret(&(data[size]),
		&(cs->player->name_len), sizeof(t_name_len));
	size += ft_memcpy_ret(&(data[size]),
		&(cs->player->name), cs->player->name_len);
	if (ft_send_protected(vm->client.socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (ft_receive_player_info(vm, cs));
}
