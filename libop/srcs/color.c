/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 20:31:49 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	color_off(void)
{
	ft_printf("%s", COLF_OFF);
}

void	color_on_term(t_color	*color)
{
	ft_printf("%s", color->term);
}

void	color_on_sdl(t_color	*color)
{
	ft_printf("%d", color->sdl);
}

void	color_on(char	*color, int index, int output)
{
	static void	(*f[2])(t_color *color) = {
		&color_on_term, &color_on_sdl};
	static t_color col_fg[NB_COLORS] = {
		{COLF_BLACK, 0}, {COLF_RED, 0}, {COLF_GREEN, 0}, {COLF_BROWN, 0},
		{COLF_BLUE, 0}, {COLF_MAGENTA, 0}, {COLF_CYAN, 0}, {COLF_GREY, 0},
		{COLF_BBLACK, 0}, {COLF_BRED, 0}, {COLF_BGREEN, 0}, {COLF_BBROWN, 0},
		{COLF_BBLUE, 0}, {COLF_BMAGENTA, 0}, {COLF_BCYAN, 0}, {COLF_BGREY, 0},
		{COLF_OFF, 0}};

	f[output](&col_fg[(int)color[index]]);
}

void	set_colors(char	*color)
{
	int		index;
	int		new_ref;
	
	index = 0;
	while(color[index])
	{
		new_ref = ft_strichr(COL_DESIGNATOR, color[index]);
		if (new_ref != -1)
			color[index] = new_ref;
		++index;
	}
}
