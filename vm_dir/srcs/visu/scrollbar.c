/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:54:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 16:12:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_scroll_scrollbar(t_vscrollbar *vscrollbar, double value)
{
	vscrollbar->state = ft_fclamp(0,
			vscrollbar->state - value *
			(double) vscrollbar->height / (double)vscrollbar->compressed_height,
			1);
}

void	ft_scroll_up(t_vm *vm, t_button *button)
{
	(void)vm;
	ft_scroll_scrollbar(button->button_union.vscrollbar, 0.03);
}

void	ft_scroll_down(t_vm *vm, t_button *button)
{
	(void)vm;
	ft_scroll_scrollbar(button->button_union.vscrollbar, -0.03);
}

int		ft_is_in_scrollbar_focus(t_vscrollbar scrollbar)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	return (ft_to_print_scrollbar(scrollbar) && scrollbar.pos_x < x &&
			scrollbar.pos.x + scrollbar.bar_width > x &&
			scrollbar.pos.y < y && scrollbar.pos.y + scrollbar.height > y);
}

void	ft_wheel_event(t_vm *vm, SDL_Event event)
{
	int i;
	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_is_in_scrollbar_focus(vm->visu.players_list[i].vscrollbar))
		{
			ft_scroll_scrollbar(&vm->visu.players_list[i].vscrollbar,
				event.wheel.y * 0.03);
			return ;
		}
		i++;
	}
}

void	ft_init_scrollbar_button(t_visu *v, t_button *button,
		t_vscrollbar *vscrollbar)
{
	button->visible = 1;
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
	v->players_list[ARENA].vscrollbar.pos_x = v->center.dashboard_x;
	xy.x = v->dim.width - v->center.scrollbar_width;
	ft_init_vscrollbar(v, xy, v->center.top_dashboard_height - xy.y,
			&v->players_list[LOCAL].vscrollbar);
	v->players_list[LOCAL].vscrollbar.pos_x = v->center.dashboard_mid_x;
	v->players_list[UPLOAD].vscrollbar.relevant = 0;

	xy.y = v->center.toolbar_y + v->center.player_h + v->center.toolbar_bottom;
	ft_init_vscrollbar(v, xy, v->dim.height - v->center.footer_height - xy.y,
			&v->players_list[SERVER].vscrollbar);
	v->players_list[SERVER].vscrollbar.pos_x = v->center.dashboard_x;
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

int		get_vscrollbar(t_vm *vm, t_ixy mouse, t_vscrollbar **vscrollbar)
{
	int i;
	t_vscrollbar *vscroll;
	i = 0;
	while (i < NB_SOURCES)
	{
		vscroll = &vm->visu.players_list[i].vscrollbar;
		if (ft_to_print_scrollbar(*vscroll))
		{
			if (mouse.x > vscroll->pos.x &&
					mouse.x < vscroll->pos.x + vscroll->bar_width &&
					mouse.y > vscroll->pos.y + vscroll->up_button.rect.h &&
					mouse.y < vscroll->pos.y + vscroll->height -
					vscroll->down_button.rect.h)
			{
				*vscrollbar = vscroll;
				return (1);
			}
		}
		i++;
	}
	return (0);
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
	new_y = ft_fclamp(y1,
			vm->visu.drag_container.y - vm->visu.drag_container.diff_y, y2);

	vscrollbar->state = (new_y - y1) / (y2 - y1);
}

void	ft_swing_scrollbar(t_vscrollbar *vscrollbar, t_ixy mouse)
{
	double	bar_height;
	double	new_y;
	double	y1;
	double	y2;

	bar_height = ft_get_vscrollbar_bar_height(*vscrollbar);
	y1 = vscrollbar->pos.y + vscrollbar->up_button.rect.h;
	y2 = vscrollbar->pos.y + vscrollbar->height -
		vscrollbar->down_button.rect.h - bar_height;
	new_y = ft_fclamp(y1,
			mouse.y - (bar_height / 2.0), y2);
	vscrollbar->state = (new_y - y1) / (y2 - y1);
}
