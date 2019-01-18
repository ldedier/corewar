/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center_play.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 20:38:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 20:39:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_init_center_memory(t_visu *visu, t_center *c)
{
	c->left_margin = MEM_BORDER_LEFT * visu->react.w_scale;
	c->right_margin = MEM_BORDER_RIGHT * visu->react.w_scale;
	c->top_margin = MEM_BORDER_TOP * visu->react.h_scale;
	c->bottom_margin = MEM_BORDER_BOTTOM * visu->react.h_scale;
	c->x_diff = X_DIFF * visu->react.w_scale;
	c->x_diff_byte = X_DIFF_BYTE * visu->react.w_scale;
	c->y_diff = Y_DIFF * visu->react.h_scale;
	c->nb_cols = MEM_COLS;
	c->nb_lines = ft_round((double)((double)MEM_SIZE /
				(double)MEM_COLS));
	while ((c->y_diff * (c->nb_lines - 1) > visu->dim.height
				- c->top_margin - c->bottom_margin) &&
			c->y_diff > 0)
		c->y_diff--;
	while ((c->x_diff * (c->nb_cols - 1) >
				c->dashboard_x - 2 * c->nb_cols *
				c->x_diff_byte) && c->x_diff > 0)
		c->x_diff--;
	c->glyph_width = (c->dashboard_x - c->left_margin - c->right_margin -
			(c->nb_cols - 1) * c->x_diff - c->nb_cols * c->x_diff_byte) /
		((double)(2 * c->nb_cols));
	c->glyph_height = (visu->dim.height - c->top_margin - c->bottom_margin -
		(c->nb_lines - 1) * c->y_diff) / ((double)c->nb_lines);
}

void	ft_init_center_entries(t_visu *visu, t_center *c)
{
	c->game_entries_h = GAME_ENTRIES_H * visu->react.h_scale;
	c->state_top = STATE_TOP * visu->react.h_scale;
	c->state_bottom = STATE_BOTTOM * visu->react.h_scale;
	c->state_h = STATE_H * visu->react.h_scale;
	c->entry_h = ENTRY_H * visu->react.h_scale;
	c->entry_bottom = ENTRY_BOTTOM * visu->react.h_scale;
	c->entry_padding = (c->game_entries_h - (c->state_top + c->state_h +
		c->state_bottom + (NB_ENTRIES * c->entry_h)
		+ c->entry_bottom)) / (double)(NB_ENTRIES - 1);
	c->entry_left = ENTRY_LEFT * visu->react.w_scale;
	c->entry_right = ENTRY_RIGHT * visu->react.w_scale;
	c->entry_space = ENTRY_SPACE * visu->react.w_scale;
	c->entry_max_w = 2 * c->dashboard_width / 3.0;
	c->entry_value_max_w = c->dashboard_width - (c->entry_left +
		c->entry_right + c->entry_space + c->entry_max_w);
	c->play_footer_h = PLAY_FOOTER_H * visu->react.h_scale;
	c->player_entries_h = visu->dim.height -
		(c->play_footer_h + c->game_entries_h);
}

void	ft_init_center_player_entries(t_visu *visu, t_center *c)
{
	c->list_player_entries_h = c->player_entries_h - c->live_breakdown_h;
	c->player_entry_left = PLAYER_ENTRY_LEFT * visu->react.w_scale;
	c->player_entry_space = PLAYER_ENTRY_SPACE * visu->react.w_scale;
	c->player_entry_height = PLAYER_ENTRY_HEIGHT * visu->react.h_scale;
	c->player_title_top = PLAYER_TITLE_TOP * visu->react.h_scale;
	c->player_title_height = PLAYER_TITLE_HEIGHT * visu->react.h_scale;
	c->player_title_bottom = PLAYER_TITLE_BOTTOM * visu->react.h_scale;
	c->list_player_entries_bottom = LIST_PLAYER_ENTRIES_B * visu->react.h_scale;
	c->player_entry_ipadding = PLAYER_ENTRY_IPADDING * visu->react.h_scale;
	c->player_entry_padding = (c->list_player_entries_h - (c->player_title_top +
		c->list_player_entries_bottom + INIT_MAX_PLAYERS *
		(c->player_title_height + c->player_title_bottom) + (INIT_MAX_PLAYERS *
			NB_PLAYER_ENTRIES * c->player_entry_height) + (INIT_MAX_PLAYERS *
				(NB_PLAYER_ENTRIES - 1) * c->player_entry_ipadding)))
					/ (double)(INIT_MAX_PLAYERS - 1);
}

void	ft_init_center_live_breakdown(t_visu *visu, t_center *c)
{
	c->live_breakdown_title_h = LIVE_BREAKDOWN_TITLE_H * visu->react.h_scale;
	c->live_breakdown_title_w = c->dashboard_width - 2 * c->entry_left;
	c->live_breakdown_title_top = LIVE_BREAKDOWN_TITLE_TOP *
		visu->react.h_scale;
	c->live_breakdown_title_left = (c->dashboard_width -
		c->live_breakdown_title_w) / 2.0;
	c->live_breakdown_bar_w = 4 * c->dashboard_width / 5.0;
	c->live_breakdown_bar_left = (c->dashboard_width -
		c->live_breakdown_bar_w) / 2.0;
	c->live_breakdown_bar_h = LIVE_BREAKDOWN_BAR_H * visu->react.h_scale;
	c->live_breakdown_bar_top = (c->live_breakdown_h -
		c->live_breakdown_bar_h) / 2.0 + c->live_breakdown_title_top;
}

void	ft_init_center_hp(t_visu *visu, t_center *c)
{
	c->live_breakdown_hp_y = c->game_entries_h + c->player_title_top +
		c->list_player_entries_bottom + 2 *
			(c->player_title_height + c->player_title_bottom) + (2 *
				NB_PLAYER_ENTRIES * c->player_entry_height) + (2 *
					(NB_PLAYER_ENTRIES - 1) * c->player_entry_ipadding) +
						c->player_entry_padding;
	c->live_breakdown_hp_h = visu->dim.height - c->live_breakdown_hp_y -
		c->play_footer_h;
	c->live_breakdown_hp_title_top = LIVE_BREAKDOWN_HP_TITLE_TOP *
		visu->react.h_scale;
	c->live_breakdown_hp_title_bottom = LIVE_BREAKDOWN_HP_TITLE_BOTTOM *
		visu->react.h_scale;
	c->live_breakdown_hp_players_h = LIVE_BREAKDOWN_HP_PLAYERS_H *
	visu->react.h_scale;
	c->live_breakdown_hp_players_bottom = LIVE_BREAKDOWN_HP_PLAYERS_BOTTOM *
		visu->react.h_scale;
	c->live_breakdown_hp_anim_y = c->live_breakdown_hp_y +
		c->live_breakdown_hp_title_top + c->live_breakdown_title_h +
			c->live_breakdown_hp_title_bottom + c->live_breakdown_hp_players_h +
				c->live_breakdown_hp_players_bottom;
	c->live_breakdown_hp_anim_h = c->game_entries_h + c->player_entries_h -
		c->live_breakdown_hp_anim_y;
	c->live_breakdown_hp_players_side = LIVE_BREAKDOWN_HP_PLAYERS_SIDE *
		visu->react.w_scale;
}
