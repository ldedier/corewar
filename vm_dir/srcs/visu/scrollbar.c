/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:54:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/17 17:24:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_scroll_up(t_vm *vm, t_button *button, t_ixy xy)
{
	(void)xy;
	(void)vm;
	(void)button;
}

void	ft_scroll_down(t_vm *vm, t_button *button, t_ixy xy)
{
	(void)xy;
	(void)vm;
	(void)button;
}

void	ft_init_scrollbar_button(t_visu *v, t_button *button,
			t_vscrollbar *vscrollbar)
{
	button->visible = 1;
	button->scrollbar = vscrollbar;
	button->rect.w = vscrollbar->bar_width;
	button->rect.h = v->center.scrollbar_buttons_height;
	button->rect.x = vscrollbar->pos.x;
	if (button == &vscrollbar->up_button)
	{
		button->on_click = &ft_scroll_up;
		button->surface = v->sdl.images[SCROLL_UP];
		button->rect.y = vscrollbar->pos.y;
	}
	else
	{
		button->on_click = &ft_scroll_down;
		button->surface = v->sdl.images[SCROLL_DOWN];
		button->rect.y = vscrollbar->pos.y + vscrollbar->height - button->rect.h;
	}
	ft_printf("%d %d %d %d\n", button->rect.w, button->rect.h, button->rect.x, button->rect.y);
	ft_printf("%d %d\n", v->dim.width, v->dim.height);
}

void	ft_init_vscrollbar(t_visu *v, t_ixy xy, int height, t_vscrollbar *vscrollbar)
{
	vscrollbar->pos = xy;
	vscrollbar->height = height;
	vscrollbar->bar_width = v->center.scrollbar_width;
	ft_init_scrollbar_button(v, &vscrollbar->up_button, vscrollbar);
	ft_init_scrollbar_button(v, &vscrollbar->down_button, vscrollbar);
//	vscrollbar->bar_y = vscrollbar->pos.y + vscrollbar.up_button.rect.h;
}

void	ft_init_players_list(t_visu *v)
{
	int		i;
	t_ixy	xy;

	i = 0;
	while (i < NB_SOURCES)
	{
		v->players_list[i].source = i;
		v->players_list[i].vscrollbar.relevant = 1;
		i++;
	}
	xy.x = v->center.dashboard_x +
		v->center.dashboard_mid_width -
			v->center.scrollbar_width;
	xy.y = v->center.title_top + v->center.title_h +
		v->center.title_bottom;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[ARENA].vscrollbar);
	xy.x = v->dim.width - v->center.scrollbar_width;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[LOCAL].vscrollbar);
	v->players_list[UPLOAD].vscrollbar.relevant = 0;

	xy.y = v->center.toolbar_y + v->center.player_h + v->center.toolbar_bottom;
	ft_init_vscrollbar(v, xy, v->dim.height - v->center.footer_height - xy.y,
			&v->players_list[SERVER].vscrollbar);
}

int		ft_get_vscrollbar_compressed_height(t_visu *v, int nb_players)
{
	return (nb_players * v->center.player_h +
			(nb_players - 1) * v->center.player_padding +
			v->center.player_top + v->center.player_bottom);
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
}

void	ft_update_scrollbar(t_vm *vm, t_vscrollbar *vscrollbar)
{
	double	bar_height;
	double	new_y;
	double	y1;
	double	y2;

	bar_height = ft_get_vscrollbar_bar_height(*vscrollbar);
	y1 = vscrollbar->pos.y + vscrollbar->up_button.rect.h;
	y2 = vscrollbar->pos.y + vscrollbar->height -
			vscrollbar->down_button.rect.h - bar_height;
	new_y = ft_fclamp(vscrollbar->pos.y + vscrollbar->up_button.rect.h,
			vm->visu.drag_container.y - vm->visu.drag_container.diff_y,
			vscrollbar->pos.y + vscrollbar->height
			- vscrollbar->down_button.rect.h - bar_height);
	
	vscrollbar->state = (new_y - y1) / (y2 - y1);
//	ft_printf("%d\n", new_y);
	(void)vm;
}
