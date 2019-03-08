/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 22:25:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/06 20:42:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_upload_result(t_vm *vm, int nb_bytes)
{
	t_flag flag;

	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	ft_memcpy(&flag, vm->client.buffer, sizeof(t_flag));
	if (flag == UPLOAD_NAME_TAKEN)
		ft_set_notification(vm, NAME_TAKEN_NOTIF);
	if (flag == UPLOAD_NAME_INVALID)
		ft_set_notification(vm, NAME_INVALID_NOTIF);
	else if (flag == FLAG_NEW_CORES)
		ft_get_new_cores(nb_bytes, vm);
	return (0);
}

int		ft_receive_upload_result(t_vm *vm)
{
	int nb_bytes;

	if (SDLNet_CheckSockets(vm->client.socket_set, TIMEOUT_LIMIT))
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
		ft_printf("no response from server for too long\n");
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
	{
		free(data);
		return (1);
	}
	free(data);
	return (ft_receive_upload_result(vm));
}
