/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:04:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 22:04:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_render_horizontal_line_dashboard(t_vm *vm, int y, int col)
{
	int		i;
	int		*pix;

	pix = (int *)vm->visu.sdl.w_surface->pixels;
	i = vm->visu.center.dashboard_x;
	while (i < vm->visu.sdl.w_surface->w)
	{
		pix[y * vm->visu.sdl.w_surface->w + i] = col;
		i++;
	}
}

void	ft_render_dashboard_separator(t_vm *vm)
{
	int		i;
	int		*pix;

	i = 0;
	pix = (int *)vm->visu.sdl.w_surface->pixels;
	while (i < vm->visu.sdl.w_surface->h)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w +
				vm->visu.center.dashboard_x)] = LINE_COL;
		i++;
	}
}

void	ft_render_init_lines(t_vm *vm)
{
	int		i;
	int		*pix;

	i = 0;
	pix = (int *)vm->visu.sdl.w_surface->pixels;
	ft_render_horizontal_line_dashboard(vm,
			vm->visu.center.title_h + vm->visu.center.title_top +
			vm->visu.center.title_bottom - 1, LINE_COL_DARKER);
	ft_render_horizontal_line_dashboard(vm,
		vm->visu.center.top_dashboard_height, LINE_COL);
	ft_render_horizontal_line_dashboard(vm,
		vm->visu.center.top_dashboard_height +
			vm->visu.center.top_dashboard_fheight, LINE_COL);
	i = 0;
	while (i < vm->visu.center.top_dashboard_height +
		vm->visu.center.top_dashboard_fheight)
	{
		pix[(int)(i * vm->visu.sdl.w_surface->w +
				vm->visu.center.dashboard_mid_x)] = LINE_COL;
		i++;
	}
}
