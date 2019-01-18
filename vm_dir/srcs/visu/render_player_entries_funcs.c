/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_entries_funcs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:45:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 19:48:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_last_live(t_vm *vm, t_player player, int y)
{
	char *value;

	(void)player;
	if (!(value = ft_itoa(player.last_live_cycle)))
		return (1);
	if (ft_render_player_entry(vm, "last live", value, y))
		return (1);
	return (0);
}

int		ft_render_nb_process(t_vm *vm, t_player player, int y)
{
	char *value;

	(void)player;
	if (!(value = ft_itoa(player.nb_proc)))
		return (1);
	if (ft_render_player_entry(vm, "nb process", value, y))
		return (1);
	return (0);
}

int		ft_render_nb_live(t_vm *vm, t_player player, int y)
{
	char *value;

	(void)player;
	if (!(value = ft_itoa(player.live)))
		return (1);
	if (ft_render_player_entry(vm,
			"lives received for current period", value, y))
		return (1);
	return (0);
}
