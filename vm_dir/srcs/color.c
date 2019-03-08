/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:27:27 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/07 18:25:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_colors_term(t_vm *vm)
{
	int			i;
	static char	*color[4] = {COLF_BRED, COLF_BGREEN, COLF_BBLUE, COLF_BBROWN};

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (!vm->visu.active && vm->display.status == ON)
			ft_memmove(vm->player[i].color.term, color[i], 11);
		else
			ft_bzero(&vm->player[i].color.term, 11);
	}
	if (vm->visu.active || vm->display.status == OFF)
	{
		ft_bzero(&vm->color, sizeof(t_color));
		return ;
	}
	ft_memmove(vm->color.cycle, COL_CYCLES, 11);
	ft_memmove(vm->color.death, COL_DEATH, 11);
	ft_memmove(vm->color.resize, COL_RESIZE, 11);
	ft_memmove(vm->color.off, EOC, 7);
}

int			get_color_sdl(int index)
{
	static int color[5] = {COL_OFF, COL_GREEN, COL_RED, COL_BBLUE, COL_BROWN};

	return (color[(int)index]);
}

int			set_color_sdl(t_vm *vm, t_player *player)
{
	int				index_min_count;
	int				i;
	static char		color_count[MAX_PLAYERS];

	(void)vm;
	if (!player->relevant)
	{
		if (player->color.value != 1)
		{
			player->color.value = 1;
			color_count[player->color.index - 1] = 0;
		}
		return (0);
	}
	if (player->color.value != 1)
		return (0);
	index_min_count = 1;
	i = 0;
	while (i < MAX_PLAYERS && color_count[i])
		++i;
	index_min_count = i;
	color_count[index_min_count] = 1;
	player->color.index = index_min_count + 1;
	player->color.value = get_color_sdl(index_min_count + 1);
	return (1);
}
