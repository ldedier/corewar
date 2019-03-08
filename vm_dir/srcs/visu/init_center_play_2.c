/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center_play_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 20:38:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 21:27:47 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_init_center_hp_2(t_visu *visu, t_center *c)
{
	double side;

	c->live_breakdown_hp_anim_y = c->live_breakdown_hp_y
		+ c->live_breakdown_hp_title_top + c->live_breakdown_title_h
		+ c->live_breakdown_hp_title_bottom + c->live_breakdown_hp_players_h
		+ c->live_breakdown_hp_players_bottom;
	c->live_breakdown_hp_anim_h = c->game_entries_h + c->player_entries_h
		- c->live_breakdown_hp_anim_y;
	side = LIVE_BREAKDOWN_HP_PLAYERS_SIDE * visu->react.w_scale;
	c->live_breakdown_hp_players_side = side;
}

void		ft_init_center_hp(t_visu *visu, t_center *c)
{
	double	len;

	c->live_breakdown_hp_y = c->game_entries_h + c->player_title_top
		+ c->list_player_entries_bottom
		+ 2 * (c->player_title_height + c->player_title_bottom)
		+ (2 * NB_PLAYER_ENTRIES * c->player_entry_height)
		+ (2 * (NB_PLAYER_ENTRIES - 1) * c->player_entry_ipadding)
		+ c->player_entry_padding;
	c->live_breakdown_hp_h = visu->dim.height - c->live_breakdown_hp_y
		- c->play_footer_h;
	len = LIVE_BREAKDOWN_HP_TITLE_TOP * visu->react.h_scale;
	c->live_breakdown_hp_title_top = len;
	len = LIVE_BREAKDOWN_HP_TITLE_BOTTOM * visu->react.h_scale;
	c->live_breakdown_hp_title_bottom = len;
	len = LIVE_BREAKDOWN_HP_PLAYERS_H * visu->react.h_scale;
	c->live_breakdown_hp_players_h = len;
	len = LIVE_BREAKDOWN_HP_PLAYERS_BOTTOM * visu->react.h_scale;
	c->live_breakdown_hp_players_bottom = len;
	ft_init_center_hp_2(visu, c);
}
