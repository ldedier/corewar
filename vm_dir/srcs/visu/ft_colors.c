/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/10 00:03:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_color_manager			ft_scale_color(t_color_manager c, double t)
{
	t_color_manager ret;

	ret.r = ft_clamp(0, c.r * t, 255);
	ret.g = ft_clamp(0, c.g * t, 255);
	ret.b = ft_clamp(0, c.b * t, 255);
	ret.color = (ret.r << 16) | (ret.g << 8) | ret.b;
	return (ret);
}

t_color_manager			ft_interpolate_color(int col1, int col2, double t)
{
	t_color_manager c1;
	t_color_manager c2;
	t_color_manager c3;

	c1 = ft_get_color(col1);
	c2 = ft_get_color(col2);

	c3.r = t * c1.r + (1 - t) * c2.r;
	c3.g = t * c1.g + (1 - t) * c2.g;
	c3.b = t * c1.b + (1 - t) * c2.b;
	c3.color = (c3.r << 16) | (c3.g << 8) | c3.b;
	return (c3);
}

t_color_manager			ft_get_color(int color)
{
	t_color_manager c;

	c.color = color;
	c.r = (color >> 16) & (0xff);
	c.g = (color >> 8) & (0xff);
	c.b = (color) & (0xff);
	return (c);
}
