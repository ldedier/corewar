/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:35:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:59:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_sort_alpha(void *p1, void *p2)
{
	t_player	*player1;
	t_player	*player2;
	int			ret;

	player1 = (t_player *)p1;
	player2 = (t_player *)p2;
	if ((ret = ft_strcmp_no_case(player1->name, player2->name)))
		return (ret);
	return (player1->score - player2->score);
}

int			ft_sort_score(void *p1, void *p2)
{
	t_player	*player1;
	t_player	*player2;
	int			ret;

	player1 = (t_player *)p1;
	player2 = (t_player *)p2;
	if ((ret = player2->score - player1->score))
		return (ret);
	return (ft_strcmp_no_case(player1->name, player2->name));
}

int			ft_sort_alpha_cs(void *client_slot_1, void *client_slot_2)
{
	t_client_slot	*cs1;
	t_client_slot	*cs2;
	int				ret;

	cs1 = (t_client_slot *)client_slot_1;
	cs2 = (t_client_slot *)client_slot_2;
	if ((ret = ft_strcmp_no_case(cs1->player->name, cs2->player->name)))
		return (ret);
	return (cs1->player->score - cs2->player->score);
}

int			ft_sort_score_cs(void *client_slot_1, void *client_slot_2)
{
	t_client_slot	*cs1;
	t_client_slot	*cs2;
	int				ret;

	cs1 = (t_client_slot *)client_slot_1;
	cs2 = (t_client_slot *)client_slot_2;
	if ((ret = cs2->player->score - cs1->player->score))
		return (ret);
	return (ft_strcmp_no_case(cs1->player->name, cs2->player->name));
}

void		ft_sort_client_slots(t_vm *vm)
{
	ft_lst_mergesort(&vm->client.client_slots,
		vm->visu.sort_cs_func, vm->visu.inv_sort);
}
