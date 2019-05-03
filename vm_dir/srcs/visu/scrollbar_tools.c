/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:55:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 16:30:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_get_scrolled_height(t_vscrollbar vscrollbar)
{
	int		val;

	val = vscrollbar.compressed_height - vscrollbar.height;
	val *= vscrollbar.state;
	if (vscrollbar.relevant)
		return (val);
	else
		return (0);
}

double		ft_get_vscrollbar_bar_height(t_vscrollbar vscrollbar)
{
	return ((vscrollbar.height - 2 * vscrollbar.up_button.rect.h)
			* ((double)(vscrollbar.height)
			/ ((double)vscrollbar.compressed_height)));
}

t_ixy		ft_get_vscrollbar_bar_height_y(t_vscrollbar vscrollbar)
{
	t_ixy	res;
	double	y1;
	double	y2;

	res.x = ((vscrollbar.height - 2 * vscrollbar.up_button.rect.h)
			* ((double)(vscrollbar.height)
			/ ((double)vscrollbar.compressed_height)));
	y1 = vscrollbar.pos.y + vscrollbar.up_button.rect.h;
	y2 = vscrollbar.pos.y + vscrollbar.height
		- vscrollbar.down_button.rect.h - res.x;
	res.y = y1 + (y2 - y1) * vscrollbar.state;
	return (res);
}

int			ft_to_print_scrollbar(t_vscrollbar vscrollbar)
{
	return (vscrollbar.relevant
			&& vscrollbar.compressed_height > vscrollbar.height);
}
