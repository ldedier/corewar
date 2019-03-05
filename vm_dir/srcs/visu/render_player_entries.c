/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_entries.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:34:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:48:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int (*g_print_player_entry_value[NB_PLAYER_ENTRIES])
	(t_vm *, t_player, int y) = {
	ft_render_last_live,
	ft_render_nb_process,
	ft_render_nb_live
};

int		ft_render_player_entry(t_vm *vm, char *entry, char *value, int y)
{
	SDL_Rect rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.player_entry_left;
	rect.y = y;
	rect.w = vm->visu.center.entry_max_w;
	rect.h = vm->visu.center.player_entry_height;
	if (ft_copy_str_to_surface_no_source(vm, entry, rect, 0))
	{
		free(value);
		return (1);
	}
	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left
		+ rect.w + vm->visu.center.entry_space;
	rect.w = vm->visu.center.entry_value_max_w;
	if (ft_copy_str_to_surface_no_source(vm, value, rect, 0))
	{
		free(value);
		return (1);
	}
	free(value);
	return (0);
}

int		ft_render_player_title(t_vm *vm, t_player player, int y)
{
	char		*tmp;
	char		*str;
	SDL_Rect	rect;
	char		abbrev[ABBREV_LEN + 2];

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.entry_left;
	rect.y = y;
	rect.w = vm->visu.center.entry_max_w;
	rect.h = vm->visu.center.player_title_height;
	if (!(tmp = ft_itoa(player.num)))
		return (1);
	if (!(str = ft_strjoin("Player ", tmp)))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	ft_copy_str_to_surface_no_source(vm, str, rect, player.color.index);
	free(str);
	rect.x = rect.x + rect.w + vm->visu.center.entry_space;
	rect.w = vm->visu.center.entry_value_max_w;
	ft_copy_abbrev(abbrev, player.name);
	ft_copy_str_to_surface_no_source(vm, abbrev, rect, player.color.index);
	return (0);
}

int		ft_render_player_entry_bloc(t_vm *vm, t_player player, int *y)
{
	int i;

	if (ft_render_player_title(vm, player, *y))
		return (1);
	*y += vm->visu.center.player_title_height
		+ vm->visu.center.player_title_bottom;
	i = 0;
	while (i < NB_PLAYER_ENTRIES)
	{
		g_print_player_entry_value[i](vm, player, *y);
		*y += vm->visu.center.player_entry_height;
		i++;
		if (i < NB_PLAYER_ENTRIES)
			*y += vm->visu.center.player_entry_ipadding;
	}
	return (0);
}

int		ft_render_player_entries(t_vm *vm)
{
	int y;
	int i;

	y = vm->visu.center.game_entries_h + vm->visu.center.player_title_top;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
		{
			if (ft_render_player_entry_bloc(vm, vm->player[i], &y))
				return (1);
			y += vm->visu.center.player_entry_padding;
		}
		i++;
	}
	return (0);
}
