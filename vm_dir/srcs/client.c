/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:54:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/20 15:41:54 by ldedier          ###   ########.fr       */
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

void	ft_download(t_vm *vm, t_button *this, t_ixy xy)
{
	(void)xy;
	(void)vm;
	if (!this->button_union.client_slot->downloaded)
	{
		this->enabled = 0;
		this->button_union.client_slot->downloaded = 1;
	}
}

void	ft_populate_download_button(t_client_slot *client_slot,
			t_button *button)
{
	button->visible = 1;
	button->enabled = 1;
	button->button_union.client_slot = client_slot;
	button->on_click = &ft_download;
	button->on_press = &nothing_on_press;
	button->render = &ft_render_download_button;
}

t_client_slot	*ft_new_client_slot(t_player *player)
{
	t_client_slot *slot;

	if (!(slot = (t_client_slot*)malloc(sizeof(t_slot))))
		return (NULL);
	slot->player = player;
	slot->downloaded = 0;
	ft_populate_download_button(slot, &slot->download);
	return (slot);
}

int		ft_add_new_client_slot(t_client *client, int i, t_name_len name_len,
		t_score score)
{
	t_client_slot	*slot;
	t_player		*player;

	if (!(player = ft_new_player(&(client->buffer[i]), name_len, score)))
		return (1);
	if (!(slot = ft_new_client_slot(player)))
	{
		free(player);
		return (1);
	}
	if (ft_add_to_list_ptr_back(&(client->client_slots), slot, sizeof(t_slot)))
	{
		free(slot);
		free(player);
		return (1);
	}
	return (0);
}

int		ft_process_add_client_slots(int nb_bytes, t_client *client)
{
	t_nb_players	nb_players;
	t_name_len		name_len;
	t_score			score;
	t_nb_players	player_iter;
	int				i;

	(void)nb_bytes;
	i = sizeof(t_flag);
	nb_players = (t_nb_players)client->buffer[i];
	i += sizeof(nb_players);
	player_iter = 0;
	while (player_iter < nb_players)
	{
		score = (t_score)(client->buffer[i]);
		i += sizeof(score);
		name_len = (t_name_len)(client->buffer[i]);
		i += sizeof(name_len);
		if (ft_add_new_client_slot(client, i, name_len, score))
			return (1);
		i += name_len;
		player_iter++;
	}
	return (0);
}

int		ft_process_connect_status(int nb_bytes, t_client *client)
{
	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	if ((t_flag)client->buffer[0] == GET_LIST)
	{
		if (ft_process_add_client_slots(nb_bytes, client))
			return (1);
		ft_printf(
				GREEN"successfully connected to server %s on port %d\n"EOC,
				client->server_address, client->port);
	//	ft_print_players(client->players);
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
	if (ft_receive_connect_status(&(vm->client)))
		return (1);
	vm->visu.players_list[SERVER].vscrollbar.compressed_height =
		ft_get_vscrollbar_compressed_height(&(vm->visu),
			ft_lstlength(vm->client.client_slots));
	return (process_visu(vm));
}
