/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_slot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:09:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 18:18:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

t_client_slot	*get_client_slot(t_vm *vm, char *name)
{
	t_list			*ptr;
	t_client_slot	*client_slot;

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
