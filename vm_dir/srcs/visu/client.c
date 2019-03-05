/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:17:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 16:27:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		ft_init_client(t_client *client)
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
	client->client_slots = NULL;
	client->upload_player.relevant = 0;
	return (0);
}

static void		ft_free_client_slot(void *cs, size_t size)
{
	t_client_slot *client_slot;

	(void)size;
	client_slot = (t_client_slot *)cs;
	free(client_slot->player);
	free(client_slot);
}

static int		ft_free_all_client(t_client *client)
{
	ft_lstdel(&client->client_slots, &ft_free_client_slot);
	SDLNet_TCP_Close(client->socket);
	SDLNet_FreeSocketSet(client->socket_set);
	return (1);
}

int				process_client(t_vm *vm)
{
	int ret;
	int	height;

	if (SDLNet_Init() == -1)
		return (ft_net_error());
	if (ft_init_client(&(vm->client)))
		return (ft_free_all_client(&vm->client));
	if (ft_receive_connect_status(vm))
		return (ft_free_all_client(&vm->client));
	height = ft_get_vscrollbar_compressed_height(&(vm->visu),
			ft_lstlength(vm->client.client_slots));
	vm->visu.players_list[SERVER].vscrollbar.compressed_height = height;
	ret = (process_visu(vm));
	ft_free_all_client(&(vm->client));
	return (ret);
}
