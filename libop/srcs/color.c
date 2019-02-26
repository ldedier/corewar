/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 21:35:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void		color_off(void)
{
	ft_printf("%s", COLF_OFF);
}

void		*get_color_ptr(char index)
{
	(void)index;
	static t_color_type color[4] = {
		{COL_MAGENTA, COLF_RED},
		{COL_GREEN, COLF_GREEN},
		{COL_BLUE, COLF_BLUE},
		{COL_BROWN, COLF_BROWN}};

	return ((void *)&color[(int)index]);
}

void		color_on_term(char index)
{
	ft_printf("%s", (char *)(get_color_ptr(index) + sizeof(int)));
}

int			get_color_sdl(char index)
{
	return (*(int *)get_color_ptr(index));
}

int			set_color(t_player *player, char *color_index_ref) // virer tout le micmac couleurs?
{
	static char	color_counter[MAX_PLAYERS];
	static int color_ref[MAX_PLAYERS] = {COL_MAGENTA, COL_GREEN, COL_BLUE, COL_BROWN};
	(void)color_index_ref;
	int			index_min_count;
	int			i;

	if (!player->relevant)
	{
		if (player->color.value != 1)
		{
			--color_counter[player->color.index];
			player->color.value = 1;
		}
		return (0);
	}
	if (player->color.value)
		return (0);
	index_min_count = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (color_counter[i] < color_counter[index_min_count])
			index_min_count = i;
	}
	++color_counter[index_min_count];
	player->color.index = index_min_count;
	ft_printf("min cound  %d\n", index_min_count);
	player->color.value = color_ref[index_min_count];
//	player->color.value = get_color_ptr(color_index_ref[index_min_count]);
	return (1);
}

char		*init_color_ref(void)
{
	static char	color_ref_index[MAX_PL_COLOR];
	int			i;

	if (!color_ref_index[1])
	{
		ft_strlcat(color_ref_index, DEFAULT_COLORS, MAX_PL_COLOR);
		i = -1;
		while (color_ref_index[++i])
			color_ref_index[i] = (char)ft_strichr(COL_DESIGNATOR, color_ref_index[i]);
	}
	return (color_ref_index);
}
