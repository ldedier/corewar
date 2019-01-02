/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/02 15:23:20 by ldedier          ###   ########.fr       */
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
			(c->nb_cols - 1) * c->x_diff - c->nb_cols * c->x_diff_byte) / ((double)
				(2 * c->nb_cols));
	c->glyph_height = (visu->dim.height - c->top_margin - c->bottom_margin -
			(c->nb_lines - 1) * c->y_diff) / ((double) c->nb_lines);
}

void	ft_init_center_players(t_visu *visu, t_center *c)
{
	c->title_top = TITLE_BORDER_TOP * visu->react.h_scale;
	c->title_bottom = TITLE_BORDER_BOTTOM * visu->react.h_scale;
	c->title_side = TITLE_BORDER_SIDE * visu->react.w_scale;
	c->title_h = TITLE_HEIGHT * visu->react.h_scale;
	c->player_top = PLAYER_TOP * visu->react.h_scale;
	c->player_left = PLAYER_BORDER_LEFT * visu->react.w_scale;
	c->player_right = PLAYER_BORDER_RIGHT * visu->react.w_scale;
	c->player_padding = PLAYER_PADDING * visu->react.h_scale;
	c->player_bottom = PLAYER_BORDER_BOTTOM * visu->react.h_scale;
	c->player_inner_border = PLAYER_INNER_BORDER * ft_fmin(visu->react.w_scale,
			visu->react.h_scale);
	c->cross_border = CROSS_BORDER * ft_fmin(visu->react.w_scale,
			visu->react.h_scale);
	c->player_w = (visu->dim.width - c->dashboard_mid_x) - (c->player_left +
			c->player_right);
	c->player_h = (c->top_dashboard_height - (double)(c->title_top +
				c->title_h +
				c->title_bottom + c->player_top + ((INIT_MAX_PLAYERS - 1) *
					(c->player_padding)) + c->player_bottom)) /
						(double)INIT_MAX_PLAYERS;
}

void	ft_init_center_online(t_visu *visu, t_center *c)
{
	c->s_title_side = S_TITLE_SIDE * visu->react.w_scale;
	c->s_title_h = S_TITLE_HEIGHT * visu->react.h_scale;
	c->upload_left = UPLOAD_LEFT * visu->react.w_scale;
	c->upload_right = UPLOAD_RIGHT * visu->react.w_scale;
	c->sort_padding = SORT_PADDING * visu->react.w_scale;
	c->sort_score_right = SORT_SCORE_RIGHT * visu->react.w_scale;
	c->toolbar_blank = c->dashboard_width - ((c->player_h * 3) + c->player_w +
			c->upload_right + c->upload_left + c->sort_padding +
				c->sort_score_right);
	c->toolbar_bottom = TOOLBAR_BOTTOM * visu->react.h_scale;
	c->labscore_left = LABSCORE_LEFT * visu->react.w_scale;
	c->labscore_width = LABSCORE_WIDTH * visu->react.w_scale;
	c->labscore_right = LABSCORE_RIGHT * visu->react.w_scale;
	c->score_width = SCORE_WIDTH * visu->react.w_scale;
	c->score_right = SCORE_RIGHT * visu->react.w_scale;
	c->scrollbar_width = SCROLLBAR_WIDTH * visu->react.w_scale;
	c->scrollbar_buttons_height = SCROLLBAR_BTTN_HEIGHT * visu->react.h_scale;
	c->download_side = (c->dashboard_width - (c->labscore_left +
		c->labscore_width + c->labscore_right + c->score_width +
		c->score_right + c->player_w + c->player_h)) / 2.0;
}

void	ft_init_center_fight(t_visu *visu, t_center *c)
{
	c->fight_top = FIGHT_TOP * visu->react.h_scale;
	c->fight_bottom = FIGHT_BOTTOM * visu->react.h_scale;
	c->fight_left = FIGHT_LEFT * visu->react.w_scale;
	c->fight_right = FIGHT_RIGHT * visu->react.w_scale;
	c->fight_height = c->footer_height - c->fight_top - c->fight_bottom;
	c->fight_width = c->dashboard_width - c->fight_left - c->fight_right;
}

void	ft_init_center_spec(t_visu *visu, t_center *c)
{
	c->spec_vborder = SPEC_VBORDER * visu->react.h_scale;
	c->switch_w = (TOP_DASHBOARD_FHEIGHT - (2 * SPEC_VBORDER)) * 2 * visu->react.w_scale;
	c->spec_h = c->top_dashboard_fheight - c->spec_vborder * 2;
	c->spec_left = (c->dashboard_mid_width - c->spec_h) / 2.0;
	c->switch_left = (c->dashboard_mid_width - c->switch_w) / 2.0;

	c->notif_panel_w = NOTIF_PANEL_W * visu->react.w_scale;
	c->notif_panel_h = NOTIF_PANEL_H * visu->react.h_scale;
	c->notif_panel_left = (visu->dim.width - c->notif_panel_w) / 2;
	c->notif_panel_top = (visu->dim.height - c->notif_panel_h) / 2;
}

void	ft_init_center(t_visu *visu, t_center *c)
{
	c->dashboard_x = DASHBOARD_X * visu->react.w_scale;
	c->top_dashboard_height = TOP_DASHBOARD_HEIGHT * visu->react.h_scale;
	c->top_dashboard_fheight = TOP_DASHBOARD_FHEIGHT * visu->react.h_scale;
	c->dashboard_width = (visu->dim.width - DASHBOARD_X * visu->react.w_scale);
	c->dashboard_mid_width = c->dashboard_width / 2.0;
	c->dashboard_mid_x = c->dashboard_x + c->dashboard_mid_width;

	c->footer_height = FOOTER_HEIGHT * visu->react.h_scale;
	c->mid_dashboard_height = visu->dim.height - c->top_dashboard_height -
		c->footer_height - c->top_dashboard_fheight;
	c->footer_y = visu->dim.height - c->footer_height;
	ft_init_center_memory(visu, c);
	ft_init_center_players(visu, c);
	ft_init_center_online(visu, c);
	ft_init_center_fight(visu, c);
	ft_init_center_spec(visu, c);
	c->toolbar_y = c->top_dashboard_height + c->top_dashboard_fheight +
		c->title_top + c->s_title_h + c->title_bottom;
}
