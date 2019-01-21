/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 20:48:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/19 19:20:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void	ft_init_center_fight(t_visu *visu, t_center *c)
{
	c->fight_top = FIGHT_TOP * visu->react.h_scale;
	c->fight_bottom = FIGHT_BOTTOM * visu->react.h_scale;
	c->fight_left = FIGHT_LEFT * visu->react.w_scale;
	c->fight_right = FIGHT_RIGHT * visu->react.w_scale;
	c->fight_height = c->footer_height - c->fight_top - c->fight_bottom;
	c->fight_width = c->dashboard_width - c->fight_left - c->fight_right;
}

void	ft_init_center_footer(t_visu *visu, t_center *c)
{
	c->winner_top = WINNER_TOP * visu->react.h_scale;
	c->winner_bottom = WINNER_BOTTOM * visu->react.h_scale;
	c->winner_height = WINNER_HEIGHT * visu->react.h_scale;
	c->winner_width = 4 * c->dashboard_width / 5.0;
	c->winner_left = (c->dashboard_width - c->winner_width) / 2.0;
	c->back_width = BACK_WIDTH * visu->react.w_scale;
	c->back_height = BACK_HEIGHT * visu->react.h_scale;
	c->back_left = (c->dashboard_width - c->back_width) / 2.0;
}

void	ft_init_center_spec(t_visu *visu, t_center *c)
{
	c->spec_vborder = SPEC_VBORDER * visu->react.h_scale;
	c->switch_w = (TOP_DASHBOARD_FHEIGHT - (2 * SPEC_VBORDER)) * 2 *
		visu->react.w_scale;
	c->spec_h = c->top_dashboard_fheight - c->spec_vborder * 2;
	c->spec_left = (c->dashboard_mid_width - c->spec_h) / 2.0;
	c->switch_left = (c->dashboard_mid_width - c->switch_w) / 2.0;
	c->notif_panel_w = NOTIF_PANEL_W * visu->react.w_scale;
	c->notif_panel_h = NOTIF_PANEL_H * visu->react.h_scale;
	c->notif_panel_left = (visu->dim.width - c->notif_panel_w) / 2;
	c->notif_panel_top = (visu->dim.height - c->notif_panel_h) / 2;
}
