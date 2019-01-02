/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/02 16:02:53 by ldedier          ###   ########.fr       */
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

t_color_manager			ft_get_color(int color)
{
	t_color_manager c;

	c.color = color;
	c.r = (color >> 16) & (0xff);
	c.g = (color >> 8) & (0xff);
	c.b = (color) & (0xff);
	return (c);
}
