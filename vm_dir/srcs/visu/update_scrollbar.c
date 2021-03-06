/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scrollbar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 20:53:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:15:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_update_vscrollbar_server_compressed_size(t_vm *vm, t_visu *v)
{
	int	h;

	h = ft_get_vscrollbar_compressed_height(v,
				ft_lstlength(vm->client.client_slots));
	v->players_list[SERVER].vscrollbar.compressed_height = h;
}

void	ft_update_vscrollbar_downloads_compressed_size(t_vm *vm, t_visu *v)
{
	int	h;

	h = ft_get_vscrollbar_compressed_height(v,
					ft_lstlength(vm->visu.downloaded_players));
	v->players_list[DOWNLOADS].vscrollbar.compressed_height = h;
}
