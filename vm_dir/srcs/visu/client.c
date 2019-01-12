/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:54:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/12 10:39:11 by ldedier          ###   ########.fr       */
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

int		ft_download(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)xy;
	(void)vm;
	if (!this->button_union.client_slot->on_disk)
	{
		if (ft_query_player_bin(vm, this->button_union.client_slot))
			return (1);
		ft_lst_mergesort(&vm->visu.downloaded_players, &ft_sort_alpha, 0);
	}
	this->enabled = 0;
	this->button_union.client_slot->on_disk = 1;
	return (0);
}

void	ft_populate_download_button(t_vm *vm, t_client_slot *client_slot,
		t_button *button)
{
	button->visible = 1;
	button->enabled = 1;
	button->button_union.client_slot = client_slot;
	button->on_click = &ft_download;
	button->on_press = &nothing_on_press;
	button->surface = vm->visu.sdl.images[DL];
	button->vscrollbar = &vm->visu.players_list[SERVER].vscrollbar;
	button->render = &ft_render_download_button;
	button->phase = PHASE_INIT;
}

t_client_slot	*ft_new_client_slot(t_vm *vm, t_player *player)
{
	t_client_slot *slot;

	if (!(slot = (t_client_slot*)malloc(sizeof(t_slot))))
		return (NULL);
	slot->player = player;
	slot->downloaded = 0;
	slot->on_disk = 0;
	ft_populate_download_button(vm, slot, &slot->download);
	return (slot);
}

int		ft_add_new_client_slot(t_vm *vm, int i, t_name_len name_len,
		t_score score)
{
	t_client_slot	*slot;
	t_player		*player;

	if (!(player = ft_new_player(&(vm->client.buffer[i]), name_len, score)))
		return (1);
	if (!(slot = ft_new_client_slot(vm, player)))
	{
		free(player);
		return (1);
	}
	if (ft_add_to_list_ptr_back(&(vm->client.client_slots), slot, sizeof(t_slot)))
	{
		free(slot);
		free(player);
		return (1);
	}
	player->num = vm->nb;
	player->from_server = 1;
	return (0);
}

t_client_slot	*get_client_slot(t_vm *vm, char *name)
{
	t_list *ptr;
	t_client_slot *client_slot;

	ptr = vm->client.client_slots;
	while (ptr != NULL)
	{
		client_slot = (t_client_slot *)(ptr->content);
		if (!ft_strcmp(client_slot->player->name, name))
			return (client_slot);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_process_new_client_slot(t_vm *vm, int i, t_name_len name_len,
		t_score score)
{
	t_client_slot	*slot;
	t_player		*player;

	if (!(player = ft_new_player(&(vm->client.buffer[i]), name_len, score)))
		return (1);
	if ((slot = get_client_slot(vm, player->name)))
	{
		slot->player->score = player->score;
		free(player);
	}
	else
	{
		if (!(slot = ft_new_client_slot(vm, player)))
		{
			free(player);
			return (1);
		}
		if (ft_add_to_list_ptr_back(&(vm->client.client_slots), slot, sizeof(t_slot)))
		{
			free(slot);
			free(player);
			return (1);
		}
		player->num = vm->nb;
		player->from_server = 1;
	}
	return (0);
}

int		ft_process_add_client_slots(int nb_bytes, t_vm *vm)
{
	t_nb_players	nb_players;
	t_name_len		name_len;
	t_score			score;
	t_nb_players	player_iter;
	int				i;

	(void)nb_bytes;
	i = sizeof(t_flag);
	ft_memcpy_recv(&nb_players, vm->client.buffer, &i, sizeof(t_nb_players));
	player_iter = 0;
	while (player_iter < nb_players)
	{
		ft_memcpy_recv(&score, vm->client.buffer, &i, sizeof(t_score));
		ft_memcpy_recv(&name_len, vm->client.buffer, &i, sizeof(t_name_len));
		if (ft_add_new_client_slot(vm, i, name_len, score))
			return (1);
		i += name_len;
		player_iter++;
	}
	return (0);
}

int		ft_process_connect_status(int nb_bytes, t_vm *vm)
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
		//	ft_print_players(client->players);
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

int		ft_receive_connect_status(t_vm *vm)
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
				return (ft_process_connect_status(nb_bytes, vm));
		}
		else
			return (ft_net_error());
	}
	return (1);
}

int		ft_get_new_cores(int nb_bytes, t_vm *vm)
{
	t_nb_players    nb_players;
	t_name_len      name_len;
	t_score         score;
	t_nb_players    player_iter;
	int             i;

	(void)nb_bytes;
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
	/*
	if (ft_add_new_client_slot(vm, i, name_len, score))
		return (1);
	ft_update_download_buttons_client_rect(vm);
	ft_update_vscrollbar_server_compressed_size(vm, &(vm->visu));
	*/
	ft_lst_mergesort(&vm->client.client_slots, vm->visu.sort_cs_func, vm->visu.inv_sort);
	ft_update_download_buttons_client_rect(vm);
	ft_update_vscrollbar_server_compressed_size(vm, &(vm->visu));
	return (0);
}

int		ft_process_event(int nb_bytes, t_vm *vm)
{
	t_flag flag;
	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	ft_memcpy(&flag, vm->client.buffer, sizeof(t_flag));
	if (flag == FLAG_NEW_CORES)
		ft_get_new_cores(nb_bytes, vm);
	return (0);
}

int		ft_process_client_events(t_vm *vm)
{
	int nb_bytes;

	if (SDLNet_CheckSockets(vm->client.socket_set, 0))
	{
		if (SDLNet_SocketReady(vm->client.socket))
		{
			nb_bytes = SDLNet_TCP_Recv(vm->client.socket, vm->client.buffer,
					MAX_TCP_PACKET);
			if (nb_bytes <= 0)
			{
				ft_printf("lost connection with the server.\n");
				vm->client.active = 0;
			}
			else
				ft_process_event(nb_bytes, vm);
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
	if (SDLNet_Init() == -1)
		return (ft_net_error());
	if (ft_init_client(&(vm->client)))
		return (1);
	if (ft_receive_connect_status(vm))
		return (1);
	vm->visu.players_list[SERVER].vscrollbar.compressed_height =
		ft_get_vscrollbar_compressed_height(&(vm->visu),
				ft_lstlength(vm->client.client_slots));
	return (process_visu(vm));
}
