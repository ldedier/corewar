/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:54:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 20:07:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_is_in_scrollbar_focus(t_vscrollbar scrollbar)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	return (ft_to_print_scrollbar(scrollbar) && scrollbar.pos_x < x &&
			scrollbar.pos.x + scrollbar.bar_width > x &&
			scrollbar.pos.y < y && scrollbar.pos.y + scrollbar.height > y);
}


int		ft_get_vscrollbar_compressed_height(t_visu *v, int nb_players)
{
	return (nb_players * v->center.player_h +
			(nb_players - 1) * v->center.player_padding +
			v->center.player_top + v->center.player_bottom);
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
			if (mouse.x >= vscroll->pos.x &&
					mouse.x <= vscroll->pos.x + vscroll->bar_width &&
					mouse.y >= vscroll->pos.y + vscroll->up_button.rect.h &&
					mouse.y <= vscroll->pos.y + vscroll->height -
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
