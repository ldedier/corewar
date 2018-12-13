/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 11:26:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_color_manager			ft_scale_color(t_color_manager c, double t)
{
	t_color_manager ret;

	ret.r = c.r * t;
	ret.g = c.g * t;
	ret.b = c.b * t;
	ret.color = ret.r | (ret.g << 8) | (ret.b << 16);
	return (ret);
}

t_color_manager			ft_get_color(int color)
{
	t_color_manager c;

	c.color = color;
	c.r = color & 0xff;
	c.g = (color >> 8) & 0xff;
	c.b = (color >> 16) & 0xff;
	return (c);
}
