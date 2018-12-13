/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/13 19:18:47 by emuckens         ###   ########.fr       */
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
	ft_printf("%s", COLF_OFF);
}

void	color_on(char *color, int index)
{
	static char *col_fg[NB_COLORS] = {COLF_BLACK, COLF_RED, COLF_GREEN, COLF_BROWN, COLF_BLUE, COLF_MAGENTA, COLF_CYAN, COLF_GREY, COLF_BBLACK, COLF_BRED, COLF_BGREEN, COLF_BBROWN, COLF_BBLUE, COLF_BMAGENTA, COLF_BCYAN, COLF_BGREY, COLF_OFF};

	ft_printf("%s", col_fg[(int)color[index]]);
}

void	set_colors(char	*color)
{
	int		index;
	int		new_ref;
	
	index = 0;
	while(color[index])
	{
		new_ref = ft_strchri(COL_DESIGNATOR, color[index], 0);
		if (new_ref != -1)
			color[index] = new_ref;
		++index;
	}
}
