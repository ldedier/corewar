/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get_new_cores.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 00:29:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 00:31:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_get_new_cores(t_vm *vm, int nb_bytes,
			int *i, t_name_len *name_len)
{
	t_score			score;

	if (nb_bytes < *i + (int)sizeof(t_score))
		return (1);
	ft_memcpy_recv(&score, vm->client.buffer, i, sizeof(t_score));
	if (nb_bytes < *i + (int)sizeof(t_name_len))
		return (1);
	ft_memcpy_recv(name_len, vm->client.buffer, i, sizeof(t_name_len));
	if (nb_bytes < *i + *name_len)
		return (1);
	if (ft_process_new_client_slot(vm, *i, *name_len, score))
		return (1);
	return (0);
}

int		ft_get_new_cores(int nb_bytes, t_vm *vm)
{
	t_nb_players	nb_players;
	t_name_len		name_len;
	t_nb_players	player_iter;
	int				i;

	if (nb_bytes < (int)sizeof(t_flag))
		return (1);
	i = sizeof(t_flag);
	ft_memcpy_recv(&nb_players, vm->client.buffer, &i, sizeof(t_nb_players));
	player_iter = 0;
	while (player_iter < nb_players)
	{
		if (ft_process_get_new_cores(vm, nb_bytes, &i, &name_len))
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
