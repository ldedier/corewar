/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:54:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/05 19:14:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_init_client(t_client *client)
{
	if (!(client->socket_set = SDLNet_AllocSocketSet(1)))
		return (ft_net_error());
	if (SDLNet_ResolveHost(&(client->server_ip), client->server_address,
				client->port) == -1)
	{
		ft_dprintf(2, RED"could not resolve IP address %s on port %d\n"EOC,
			client->server_address, client->port);
		return (1);
	}
	if (!(client->socket = SDLNet_TCP_Open(&(client->server_ip))))
		return (ft_net_error());
	if (SDLNet_TCP_AddSocket(client->socket_set, client->socket) == -1)
		return (ft_net_error());
	return (0);
}

int		ft_receive_connect_status(t_client *client)
{
	if (SDLNet_CheckSockets(client->socket_set, 1500))
	{
		if (SDLNet_SocketReady(client->socket))
		{
			if (SDLNet_TCP_Recv(client->socket, &(client->received),
						sizeof(client->received)) <= 0)
				return (ft_net_error());
			else
			{
				ft_printf("WAH C CHO\n");
				return (0);
			}
		}
		else
			return (ft_net_error());
	}
	return (1);
}

int		ft_process_loop_client(t_vm *vm)
{
	(void)vm;
	return (0);
}

int		process_client(t_vm *vm)
{
	int	ret;

	//	test(*vm);
	if (SDLNet_Init() == -1)
		return (ft_net_error());
	if (ft_init_client(&(vm->client)))
		return (1);
	if (ft_receive_connect_status(&(vm->client)))
		return (1);
	else
		vm->client.running = 1;
	while (vm->client.running)
	{
		if (ft_process_loop_client(vm))
			ret = 1;
	}
	return (ret);
}
