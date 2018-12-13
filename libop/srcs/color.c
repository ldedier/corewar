/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 20:46:11 by emuckens         ###   ########.fr       */
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
		{COLF_BLACK, COL_BLACK},
		{COLF_RED, COL_RED},
		{COLF_GREEN, COL_GREEN},
		{COLF_BROWN, COL_BROWN},
		{COLF_BLUE, COL_BLUE},
		{COLF_MAGENTA, COL_MAGENTA},
		{COLF_CYAN, COL_CYAN},
		{COLF_GREY, COL_GREY},
		{COLF_BBLACK, COL_BBLACK},
		{COLF_BRED, COL_BRED},
		{COLF_BGREEN, COL_BGREEN},
		{COLF_BBROWN, COL_BBROWN},
		{COLF_BBLUE, COL_BBLUE},
		{COLF_BMAGENTA, COL_BMAGENTA},
		{COLF_BCYAN, COL_BCYAN},
		{COLF_BGREY, COL_BGREY},
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
