/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:54:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/07 00:17:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_disconnect_client(t_client *client, int ret)
{
	client->running = 0;
	return (ret);
}

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
	client->cores = NULL;
	return (0);
}

int		ft_add_new_core(t_client *client, int i, t_name_size size,
		t_score score)
{
	t_core *core;

	char *name;

	if (!(name = ft_strndup(&(client->buffer[i]), size)))
		return (1);
	if (!(core = ft_new_core(name, score)))
		return (ft_free_turn(name, 1));
	if (ft_add_to_list_ptr_back(&(client->cores), core, sizeof(t_core)))
	{
		free(name);
		free(core);
		return (1);
	}
	return (0);
}

int		ft_process_add_cores(int nb_bytes, t_client *client)
{
	t_nb_cores	nb_cores;
	t_name_size	name_size;
	t_score		score;
	t_nb_cores	core_iter;
	int			i;

	ft_printf("%d\n", nb_bytes);
	i = sizeof(t_flag);
	nb_cores = (t_nb_cores)client->buffer[i];
	i += sizeof(nb_cores);
	core_iter = 0;
	ft_printf("NBCORES: %d\n\n", nb_cores);	
	while (core_iter < nb_cores)
	{
		score = (t_score)(client->buffer[i]);
		i += sizeof(score);
		name_size = (t_name_size)(client->buffer[i]);
		i += sizeof(name_size);
		if (ft_add_new_core(client, i, name_size, score))
			return (1);
		i += name_size;
		core_iter++;
	}
	return (0);
}

int		ft_process_connect_status(int nb_bytes, t_client *client)
{
	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	if ((t_flag)client->buffer[0] == GET_LIST)
	{
		if (ft_process_add_cores(nb_bytes, client))
			return (1);
		ft_printf(
				GREEN"successfully connected to server %s on port %d\n"EOC,
				client->server_address, client->port);
		ft_print_cores(client->cores);
		return (0);
	}
	else if ((t_flag)client->buffer[0] == SERVER_FULL)
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

int		ft_receive_connect_status(t_client *client)
{
	int nb_bytes;

	if (SDLNet_CheckSockets(client->socket_set, 1500))
	{
		if (SDLNet_SocketReady(client->socket))
		{
			if ((nb_bytes = SDLNet_TCP_Recv(client->socket, client->buffer,
							MAX_TCP_PACKET)) <= 0)
				return (ft_net_error());
			else
				return (ft_process_connect_status(nb_bytes, client));
		}
		else
			return (ft_net_error());
	}
	return (1);
}

int		ft_process_loop_client(t_vm *vm)
{
	int nb_bytes;
	if (SDLNet_CheckSockets(vm->client.socket_set, 50))
	{
		if (SDLNet_SocketReady(vm->client.socket))
		{
			nb_bytes = SDLNet_TCP_Recv(vm->client.socket, vm->client.buffer,
						MAX_TCP_PACKET);
			if(nb_bytes <= 0)
			{
				ft_printf("lost connection with the server.\n");
				vm->client.running = 0;
			}
		}
		else
		{
			printf("No response from the server for too long\n");
			return (1);
		}

	}
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
		if ((ret = ft_process_loop_client(vm)))
		{
			vm->client.running = 0;
			ret	= 1;
		}
	}
	return (ret);
}
