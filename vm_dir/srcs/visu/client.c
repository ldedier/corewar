/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:17:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 18:19:26 by ldedier          ###   ########.fr       */
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
	client->client_slots = NULL;
	client->upload_player.relevant = 0;
	return (0);
}

int		ft_get_new_cores(int nb_bytes, t_vm *vm)
{
	t_nb_players	nb_players;
	t_name_len		name_len;
	t_score			score;
	t_nb_players	player_iter;
	int				i;

	(void)nb_bytes; //olalala
	i = sizeof(t_flag);
	ft_memcpy_recv(&nb_players, vm->client.buffer, &i, sizeof(t_nb_players));
	player_iter = 0;
	while (player_iter < nb_players)
	{
		ft_memcpy_recv(&score, vm->client.buffer, &i, sizeof(t_score));
		ft_memcpy_recv(&name_len, vm->client.buffer, &i, sizeof(t_name_len));
		if (ft_process_new_client_slot(vm, i, name_len, score))
			return (1);
		i += name_len;
		player_iter++;
	}
	ft_lst_mergesort(&vm->client.client_slots,
		vm->visu.sort_cs_func, vm->visu.inv_sort);
	ft_update_download_buttons_client_rect(vm);
	ft_update_vscrollbar_server_compressed_size(vm, &(vm->visu));
	return (0);
}

void	ft_free_client_slot(void *cs, size_t size)
{
	t_client_slot *client_slot;

	(void)size;
	client_slot = (t_client_slot *)cs;
	free(client_slot->player);
	free(client_slot);
}

int		ft_free_all_client(t_client *client)
{
	ft_lstdel(&client->client_slots, &ft_free_client_slot);
	SDLNet_TCP_Close(client->socket);
	SDLNet_FreeSocketSet(client->socket_set);
	return (1);
}

int		process_client(t_vm *vm)
{
	int ret;

	if (SDLNet_Init() == -1)
		return (ft_net_error());
	if (ft_init_client(&(vm->client)))
		return (ft_free_all_client(&vm->client));
	if (ft_receive_connect_status(vm))
		return (ft_free_all_client(&vm->client));
	vm->visu.players_list[SERVER].vscrollbar.compressed_height =
		ft_get_vscrollbar_compressed_height(&(vm->visu),
				ft_lstlength(vm->client.client_slots));
	ret = (process_visu(vm));
	ft_free_all_client(&(vm->client));
	return (ret);
}
