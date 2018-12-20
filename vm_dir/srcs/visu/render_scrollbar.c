/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scrollbar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:59:18 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 19:00:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_scrollbar_bar(t_vm *vm, t_vscrollbar vscrollbar)
{
	SDL_Rect rect;
	t_ixy height_y;

	rect.x = vscrollbar.pos.x;
	rect.w = vscrollbar.bar_width;
	height_y = ft_get_vscrollbar_bar_height_y(vscrollbar);
	rect.h = height_y.x;
	rect.y = height_y.y;
	if (SDL_BlitScaled(vm->visu.sdl.images[SCROLL_BAR], NULL,
			vm->visu.sdl.w_surface, &rect) < 0)
		return (ft_net_error());
	return (0);
}

int		ft_render_scrollbar_buttons(t_vm *vm, t_vscrollbar vscrollbar)
{
	if (vscrollbar.up_button.render(vm, &vscrollbar.up_button))
		return (1);
	if (vscrollbar.down_button.render(vm, &vscrollbar.down_button))
		return (1);
	return (0);
}

int		ft_render_scrollbar(t_vm *vm, t_vscrollbar vscrollbar)
{
	SDL_Rect rect;

	rect.x = vscrollbar.pos.x;
	rect.y = vscrollbar.pos.y;
	rect.w = vscrollbar.bar_width;
	rect.h = vscrollbar.height;
	SDL_FillRect(vm->visu.sdl.w_surface, &rect, 0x777777);
	ft_render_scrollbar_bar(vm, vscrollbar);
	ft_render_scrollbar_buttons(vm, vscrollbar);
	return (0);
}

int		ft_render_vscrollbars(t_vm *vm)
{
	int i;

	i = 0;
	while (i < NB_SOURCES)
	{
		if (ft_to_print_scrollbar(vm->visu.players_list[i].vscrollbar))
			ft_render_scrollbar(vm, vm->visu.players_list[i].vscrollbar);
		i++;
	}
	return (0);
}
