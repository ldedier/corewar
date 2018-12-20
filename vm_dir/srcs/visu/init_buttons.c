/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:28:15 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/20 15:43:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_populate_closing_button(t_vm *vm, t_button *button,
			t_player *player, t_ixy xy)
{
	button->rect.x = xy.x;
	button->rect.y = xy.y;
	button->rect.w = vm->visu.center.cross_border;
	button->rect.h = vm->visu.center.cross_border;
	button->surface = vm->visu.sdl.images[CLOSE];
	button->button_union.player = player;
	button->on_click = &ft_delete_player;
	button->on_press = &nothing_on_press;
	button->render = &ft_render_button;
	button->visible = 0;
	button->enabled = 1;
	button->vscrollbar = &vm->visu.players_list[ARENA].vscrollbar;
}

void	ft_init_button(t_button *button, SDL_Rect rect, SDL_Surface *surface,
			void (*on_click)(t_vm *, t_button *, t_ixy xy))
{
	button->rect = rect;
	button->surface = surface;
	button->on_click = on_click;
	button->on_press = &nothing_on_press;
	button->render = &ft_render_button;
	button->visible = 1;
	button->enabled = 1;
	button->vscrollbar = NULL;
}

void	ft_init_buttons(t_vm *vm, t_visu *visu)
{
	SDL_Rect	rect;

	rect.w = visu->center.player_h;
	rect.h = visu->center.player_h;
	rect.x = visu->center.dashboard_x + visu->center.upload_left +
		visu->center.player_w + visu->center.upload_right;
	rect.y =  visu->center.top_dashboard_height + visu->center.s_title_h +
		visu->center.title_bottom + visu->center.title_top;
	ft_init_button(&(visu->buttons[UPLOAD_BUTTON]), rect,
		vm->visu.sdl.images[UL], &ft_upload);
	visu->buttons[UPLOAD_BUTTON].enabled = 0;
	visu->buttons[UPLOAD_BUTTON].render = &ft_render_upload_button;
	rect.x += visu->center.player_h + visu->center.toolbar_blank;
	ft_init_button(&(visu->buttons[ALPHA_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_ALPHA], &nothing_on_click);
	rect.x += visu->center.player_h + visu->center.sort_padding;
	ft_init_button(&(visu->buttons[SCORE_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_SCORE], &nothing_on_click);
	rect.x = visu->center.dashboard_x + visu->center.fight_left;
	rect.y = visu->center.footer_y + visu->center.fight_top;; 
	rect.h = visu->center.fight_height;
	rect.w = visu->center.fight_width;
	ft_init_button(&(visu->buttons[FIGHT_BUTTON]), rect,
	vm->visu.sdl.images[FIGHT], &fight);
}
