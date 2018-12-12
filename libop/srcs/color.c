/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/12 21:49:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int		ft_strchri(const char *s, int c, int i)
{
	if (!c)
		return (-1);
	while (*(s + i))
	{
		if (*(s + i) == c)
			return (i);
		i++;
	}
	return (-1);
}

void	color_off(void)
{
	ft_printf("%s%s", COLF_OFF, COLB_OFF);
}

void	color_on(char *color, int index)
{
	static char *col_fg[NB_COLORS] = {COLF_BLACK, COLF_RED, COLF_GREEN, COLF_BROWN, COLF_BLUE, COLF_MAGENTA, COLF_CYAN, COLF_GREY, COLF_OFF};
	static char *col_bg[NB_COLORS] = {COLB_BLACK, COLB_RED, COLB_GREEN, COLB_BROWN, COLB_BLUE, COLB_MAGENTA, COLB_CYAN, COLB_GREY, COLB_OFF};
	int		fg;
	int		bg;

	index *= 2;
//	ft_printf("colorfg[%d] = %d\n", index, color[index]);
//	ft_printf("colorbg[%d] = %d\n", index + 1, color[index + 1]);
	fg = color[index];
	bg = color[index + 1];


//	ft_printf("index * 2 = %d val in ref = \n", index * 2, col);
	ft_printf("%s%s", col_bg[bg], col_fg[fg]);
}

void	set_colors(char	*color)
{
	int		index;
	int		new_ref;
//	char *color = "pspcplpdpvrlrarrtltmtctep0p1p2p3p4p5p6p7p8p9";
	
	index = 0;
	while(color[index])
	{
		new_ref = ft_strchri(COL_DESIGNATOR, color[index], 0);
		if (new_ref != -1)
			color[index] = new_ref;
		++index;
	}
}
