/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:15:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 16:32:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_process_connect_status(int nb_bytes, t_vm *vm)
{
	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	if ((t_flag)vm->client.buffer[0] == GET_LIST)
	{
		if (ft_process_add_client_slots(nb_bytes, vm))
			return (1);
		ft_printf(
				GREEN"successfully connected to server %s on port %d\n"EOC,
				vm->client.server_address, vm->client.port);
		ft_lst_mergesort(&vm->client.client_slots, &ft_sort_alpha_cs, 0);
		return (0);
	}
	else if ((t_flag)vm->client.buffer[0] == SERVER_FULL)
	{
		ft_printf("server is full\n");
		return (1);
	}
	else
	{
		ft_printf("unknown server response\n");
		return (1);
	}
}

int			ft_receive_connect_status(t_vm *vm)
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
				return (ft_process_connect_status(nb_bytes, vm));
		}
		else
			return (ft_net_error());
	}
	return (1);
}
