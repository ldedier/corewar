/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:16:55 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_render_button(t_vm *vm, t_button *button)
{
	if (!button->visible)
		return (0);
	if (ft_process_render_button(vm, button->rect, button->surface,
			button->vscrollbar))
		return (1);
	return (0);
}

int			ft_render_score_label(t_vm *vm, int x, int y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = vm->visu.center.labscore_width;
	rect.h = vm->visu.center.player_h;
	if (ft_blit_scaled_scrollbar(&vm->visu.sdl, vm->visu.sdl.titles[SCORE],
		rect, vm->visu.players_list[SERVER].vscrollbar) < 0)
		return (ft_net_error());
	return (0);
}

int			ft_render_client_score(t_vm *vm, int x, int y, t_client_slot *slot)
{
	char		*str;
	SDL_Rect	rect;
	t_ixy		col_source;
	int			copied_len;
	int			len;

	rect.x = x;
	rect.y = y + 7;
	rect.w = vm->visu.center.score_width;
	rect.h = vm->visu.center.player_h;
	if (!(str = ft_itoa(slot->player->score)))
		return (1);
	col_source.x = MAX_PL_COLOR;
	col_source.y = SERVER;
	len = ft_strlen(str);
	copied_len = ft_copied_char_surface_w(rect, len) * len;
	rect.x += (rect.w - copied_len) / 2.0;
	if (ft_copy_str_to_surface(vm, str, rect, col_source))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

void		ft_update_download_buttons_client_rect(t_vm *vm)
{
	t_list			*ptr;
	t_client_slot	*slot;
	double			y;
	double			x;
	int				w;

	y = vm->visu.players_list[SERVER].vscrollbar.pos.y
		+ vm->visu.center.player_top;
	w = 0;
	if (ft_to_print_scrollbar(vm->visu.players_list[SERVER].vscrollbar))
		w = vm->visu.center.scrollbar_width / 2;
	x = vm->visu.center.dashboard_x + vm->visu.center.labscore_left
		+ vm->visu.center.labscore_width + vm->visu.center.labscore_right
		+ vm->visu.center.score_width + vm->visu.center.score_right
		+ vm->visu.center.player_w + vm->visu.center.download_side - w;
	ptr = vm->client.client_slots;
	while (ptr != NULL && (slot = (t_client_slot *)(ptr->content)))
	{
		slot->download.rect.x = x;
		slot->download.rect.y = y;
		slot->download.rect.w = vm->visu.center.player_h;
		slot->download.rect.h = vm->visu.center.player_h;
		y += vm->visu.center.player_padding + vm->visu.center.player_h;
		ptr = ptr->next;
	}
}

int			ft_render_client_slot(t_vm *vm, t_client_slot *slot, int y)
{
	double	x;
	t_xy	xy;

	x = vm->visu.center.dashboard_x + vm->visu.center.labscore_left;
	if (ft_render_score_label(vm, x, y))
		return (1);
	x += vm->visu.center.labscore_width + vm->visu.center.labscore_right;
	if (ft_render_client_score(vm, x, y, slot))
		return (1);
	x += vm->visu.center.score_width + vm->visu.center.score_right;
	xy.x = x;
	xy.y = y;
	if (ft_render_player(vm, slot->player, xy, SERVER))
		return (1);
	if (slot->download.render(vm, &slot->download))
		return (1);
	return (0);
}
