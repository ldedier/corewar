/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 20:41:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 20:49:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	ft_init_center_entries(visu, c);
	c->live_breakdown_h = LIVE_BREAKDOWN_H * visu->react.h_scale;
	ft_init_center_player_entries(visu, c);
	ft_init_center_live_breakdown(visu, c);
	ft_init_center_footer(visu, c);
	ft_init_center_hp(visu, c);
	c->toolbar_y = c->top_dashboard_height + c->top_dashboard_fheight +
		c->title_top + c->s_title_h + c->title_bottom;
}
