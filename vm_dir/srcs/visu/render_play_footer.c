/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_play_footer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:00:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:47:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_render_winner(t_vm *vm, SDL_Rect rect)
{
	char		*win_str;
	char		abbrev[ABBREV_LEN + 2];
	int			len;
	int			win_str_len;

	ft_copy_abbrev(abbrev, vm->winner->name);
	if (!(win_str = ft_strjoin(abbrev, " wins !")))
		return (1);
	win_str_len = ft_strlen(win_str);
	len = ft_copied_char_surface_w(rect, win_str_len) * win_str_len;
	rect.x = rect.x + (rect.w - len) / 2.0;
	if (ft_copy_str_to_surface_no_source(vm, win_str,
				rect, vm->winner->color.index))
	{
		free(win_str);
		return (0);
	}
	free(win_str);
	return (0);
}

int		ft_render_winner(t_vm *vm)
{
	SDL_Rect	rect;

	rect.x = vm->visu.center.dashboard_x + vm->visu.center.winner_left;
	rect.y = vm->visu.center.game_entries_h + vm->visu.center.player_entries_h
		+ vm->visu.center.winner_top;
	rect.w = vm->visu.center.winner_width;
	rect.h = vm->visu.center.winner_height;
	if (vm->proc == NULL && vm->winner)
		return (ft_process_render_winner(vm, rect));
	return (0);
}

int		ft_render_play_footer(t_vm *vm)
{
	if (ft_render_winner(vm))
		return (1);
	if (ft_render_button(vm, &vm->visu.buttons[BACK_BUTTON]))
		return (1);
	return (0);
}
