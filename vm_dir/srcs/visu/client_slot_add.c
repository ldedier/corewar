/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_slot_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:09:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 00:44:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_add_client_slot(t_vm *vm, t_player *player)
{
	t_client_slot	*slot;

	if (!(slot = ft_new_client_slot(vm, player)))
	{
		free(player);
		return (1);
	}
	if (ft_add_to_list_ptr_back(&(vm->client.client_slots),
		slot, sizeof(t_slot)))
	{
		free(slot);
		free(player);
		return (1);
	}
	player->num = vm->nb;
	player->from_server = 1;
	return (0);
}

int		ft_add_new_client_slot(t_vm *vm, int i, t_name_len name_len,
		t_score score)
{
	t_player		*player;

	if (!(player = ft_new_player(&(vm->client.buffer[i]), name_len, score)))
		return (1);
	return (ft_process_add_client_slot(vm, player));
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
		return (0);
	}
	else
		return (ft_process_add_client_slot(vm, player));
}

int		ft_process_process_add_client_slots(t_vm *vm, int nb_bytes,
			int i, t_nb_players nb_players)
{
	t_name_len		name_len;
	t_score			score;
	t_nb_players	player_iter;

	player_iter = 0;
	while (player_iter < nb_players)
	{
		if (nb_bytes < (int)(i + sizeof(t_score)))
			return (1);
		ft_memcpy_recv(&score, vm->client.buffer, &i, sizeof(t_score));
		if (nb_bytes < (int)(i + sizeof(t_name_len)))
			return (1);
		ft_memcpy_recv(&name_len, vm->client.buffer, &i, sizeof(t_name_len));
		if (nb_bytes < (int)(i + name_len))
			return (1);
		if (ft_add_new_client_slot(vm, i, name_len, score))
			return (1);
		i += name_len;
		player_iter++;
	}
	return (0);
}

int		ft_process_add_client_slots(int nb_bytes, t_vm *vm)
{
	t_nb_players	nb_players;
	int				i;

	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	i = sizeof(t_flag);
	if (nb_bytes < (int)(i + sizeof(t_nb_players)))
		return (1);
	ft_memcpy_recv(&nb_players, vm->client.buffer, &i, sizeof(t_nb_players));
	return (ft_process_process_add_client_slots(vm, nb_bytes, i, nb_players));
}
