/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scrollbar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:16:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/30 21:31:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_init_scrollbar_button(t_visu *v, t_button *button,
		t_vscrollbar *vscrollbar)
{
	button->visible = 1;
	button->enabled = 1;
	button->button_union.vscrollbar = vscrollbar;
	button->rect.w = vscrollbar->bar_width;
	button->rect.h = v->center.scrollbar_buttons_height;
	button->rect.x = vscrollbar->pos.x;
	if (button == &vscrollbar->up_button)
	{
		button->on_press = &ft_scroll_up;
		button->surface = v->sdl.images[SCROLL_UP];
		button->rect.y = vscrollbar->pos.y;
	}
	else
	{
		button->on_press = &ft_scroll_down;
		button->surface = v->sdl.images[SCROLL_DOWN];
		button->rect.y = vscrollbar->pos.y + vscrollbar->height - button->rect.h;
	}
	button->on_click = &nothing_on_click;
	button->render = &ft_render_button;
}

void	ft_init_vscrollbar(t_visu *v, t_ixy xy, int height, t_vscrollbar *vscrollbar)
{
	vscrollbar->pos = xy;
	vscrollbar->height = height;
	vscrollbar->bar_width = v->center.scrollbar_width;
	ft_init_scrollbar_button(v, &vscrollbar->up_button, vscrollbar);
	ft_init_scrollbar_button(v, &vscrollbar->down_button, vscrollbar);
}

void	ft_init_players_list(t_vm *vm, t_visu *v)
{
	int		i;
	t_ixy	xy;

	i = -1;
	while (++i < NB_SOURCES)
	{
		v->players_list[i].source = i;
		v->players_list[i].vscrollbar.relevant = 1;
	}
	xy.x = v->center.dashboard_x + v->center.dashboard_mid_width -
		v->center.scrollbar_width;
	xy.y = v->center.title_top + v->center.title_h + v->center.title_bottom;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[ARENA].vscrollbar);
	v->players_list[ARENA].vscrollbar.pos_x = v->center.dashboard_x;
	xy.x = v->dim.width - v->center.scrollbar_width;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[LOCAL].vscrollbar);
	v->players_list[LOCAL].vscrollbar.pos_x = v->center.dashboard_mid_x;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[DOWNLOADS].vscrollbar);
	v->players_list[LOCAL].vscrollbar.relevant = vm->nb_players;
	v->players_list[DOWNLOADS].vscrollbar.relevant = !vm->nb_players;
	v->players_list[DOWNLOADS].vscrollbar.pos_x = v->center.dashboard_mid_x;
	v->players_list[UPLOAD].vscrollbar.relevant = 0;
	xy.y = v->center.toolbar_y + v->center.player_h + v->center.toolbar_bottom;
	ft_init_vscrollbar(v, xy, v->dim.height - v->center.footer_height - xy.y,
		&v->players_list[SERVER].vscrollbar);
	v->players_list[SERVER].vscrollbar.pos_x = v->center.dashboard_x;
}

void	ft_init_vscrollbars_compressed_size(t_vm *vm, t_visu *v)
{
	v->players_list[ARENA].vscrollbar.compressed_height =
		ft_get_vscrollbar_compressed_height(v, MAX_PLAYERS);
	v->players_list[LOCAL].vscrollbar.compressed_height =
		ft_get_vscrollbar_compressed_height(v, vm->nb_players);
	if (vm->client.active)
		v->players_list[SERVER].vscrollbar.compressed_height =
			ft_get_vscrollbar_compressed_height(v,
					ft_lstlength(vm->client.client_slots));
	v->players_list[DOWNLOADS].vscrollbar.compressed_height =
			ft_get_vscrollbar_compressed_height(v,
					ft_lstlength(vm->visu.downloaded_players));
}
