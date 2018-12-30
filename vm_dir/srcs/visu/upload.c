/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 22:25:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/31 00:04:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_upload_result(t_vm *vm, int nb_bytes)
{
	(void)nb_bytes;
	if ((t_flag)vm->client.buffer[0] == UPLOAD_SUCCESS)
		ft_printf("ouai\n");
	else if ((t_flag)vm->client.buffer[0] == UPLOAD_NAME_TAKEN)
		ft_printf("nope\n");
	return (0);
}

int		ft_receive_upload_result(t_vm *vm)
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
				return (ft_process_upload_result(vm, nb_bytes));
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

int		ft_process_upload(t_vm *vm, t_player player)
{
	char	*data;
	int		i;
	int		size;

	size = sizeof(t_flag) + sizeof(t_file_len) + player.file_len;
	if (!(data = (char *)malloc(size)))
		return (1);
	i = 0;
	vm->client.flag = FLAG_UPLOAD;
	i += ft_memcpy_ret(&(data[i]), &(vm->client.flag), sizeof(t_flag));
	i += ft_memcpy_ret(&(data[i]), &(player.file_len), sizeof(t_file_len));
	i += ft_memcpy_ret(&(data[i]), player.bin, player.file_len);
	if (ft_send_protected(vm->client.socket, data, size))
		return (1);
	return (ft_receive_upload_result(vm));
}
