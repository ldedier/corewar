/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:28:15 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 19:01:02 by ldedier          ###   ########.fr       */
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
	button->phase = PHASE_INIT;
}

void	ft_init_button(t_button *button, SDL_Rect rect, SDL_Surface *surface,
			int (*on_click)(t_vm *, t_button *, t_ixy xy))
{
	button->rect = rect;
	button->surface = surface;
	button->on_click = on_click;
	button->on_press = &nothing_on_press;
	button->render = &ft_render_button;
	button->visible = 1;
	button->enabled = 1;
	button->vscrollbar = NULL;
	button->phase = PHASE_INIT;
}

void	ft_init_buttons_3(t_vm *vm, t_visu *visu)
{
	SDL_Rect	rect;

	rect.x = visu->center.notif_panel_left +
		3 * (visu->center.notif_panel_w) / 8.0;
	rect.y = visu->center.notif_panel_top +
		(3.0 * visu->center.notif_panel_h) / 4.0;
	rect.w = visu->center.notif_panel_w / 4.0;
	rect.h = visu->center.notif_panel_h / 8.0;
	ft_init_button(&(visu->buttons[OK_BUTTON]), rect,
	vm->visu.sdl.images[OK], &ft_remove_notification);
	visu->buttons[OK_BUTTON].visible = 0;
	rect.x = visu->center.dashboard_x + visu->center.back_left;
	rect.y = visu->center.game_entries_h + visu->center.player_entries_h +
		visu->center.winner_top + visu->center.winner_height +
			visu->center.winner_bottom;
	rect.w = visu->center.back_width;
	rect.h = visu->center.back_height;
	ft_init_button(&(visu->buttons[BACK_BUTTON]), rect,
		vm->visu.sdl.images[BACK], &go_back);
	visu->buttons[BACK_BUTTON].phase = PHASE_PLAY;
}

void	ft_init_buttons_2(t_vm *vm, t_visu *visu)
{
	SDL_Rect	rect;

	rect.x = visu->center.dashboard_x + visu->center.fight_left;
	rect.y = visu->center.footer_y + visu->center.fight_top;
	rect.h = visu->center.fight_height;
	rect.w = visu->center.fight_width;
	ft_init_button(&(visu->buttons[FIGHT_BUTTON]), rect,
	vm->visu.sdl.images[FIGHT], &fight);
	rect.x = visu->center.dashboard_x + visu->center.spec_left;
	rect.y = visu->center.top_dashboard_height + visu->center.spec_vborder;
	rect.h = visu->center.spec_h;
	rect.w = visu->center.spec_h;
	ft_init_button(&(visu->buttons[CLEAN_ARENA_BUTTON]), rect,
	vm->visu.sdl.images[TRASH], &clean_arena);
	visu->buttons[CLEAN_ARENA_BUTTON].render = ft_render_trash_button;
	visu->buttons[CLEAN_ARENA_BUTTON].enabled = vm->nb_players;
	rect.w = visu->center.switch_w;
	rect.x = visu->center.dashboard_x + visu->center.dashboard_mid_width +
		visu->center.switch_left;
	ft_init_button(&(visu->buttons[SWITCH_LOCAL_BUTTON]), rect,
	vm->visu.sdl.images[SWITCH_1], &switch_local);
	visu->buttons[SWITCH_LOCAL_BUTTON].render = ft_render_switch_button;
	ft_init_buttons_3(vm, visu);
}

void	ft_init_buttons(t_vm *vm, t_visu *visu)
{
	SDL_Rect	rect;

	rect.w = visu->center.player_h;
	rect.h = visu->center.player_h;
	rect.x = visu->center.dashboard_x + visu->center.upload_left +
		visu->center.player_w + visu->center.upload_right;
	rect.y = visu->center.top_dashboard_height +
		visu->center.top_dashboard_fheight + visu->center.s_title_h +
			visu->center.title_bottom + visu->center.title_top;
	ft_init_button(&(visu->buttons[UPLOAD_BUTTON]), rect,
		vm->visu.sdl.images[UL], &ft_upload);
	visu->buttons[UPLOAD_BUTTON].enabled = 0;
	visu->buttons[UPLOAD_BUTTON].render = &ft_render_upload_button;
	rect.x += visu->center.player_h + visu->center.toolbar_blank;
	ft_init_button(&(visu->buttons[ALPHA_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_ALPHA], &sort_alpha);
	rect.x += visu->center.player_h + visu->center.sort_padding;
	ft_init_button(&(visu->buttons[SCORE_SORT_BUTTON]), rect,
		vm->visu.sdl.images[SORT_SCORE], &sort_score);
	ft_init_buttons_2(vm, visu);
}
