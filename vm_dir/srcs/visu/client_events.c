/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:07:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 21:24:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
				vm->visu.players_list[SERVER].vscrollbar.relevant = 0;
				ft_set_notification(vm, LOST_CONNEXION_NOTIF);
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
