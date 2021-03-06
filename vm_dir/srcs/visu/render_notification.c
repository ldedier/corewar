/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 19:39:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 20:28:14 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_set_notification(t_vm *vm, int image_index)
{
	vm->visu.notification.image_index = image_index;
	vm->visu.buttons[OK_BUTTON].visible = 1;
}

int			ft_remove_notification(t_vm *vm, t_button *button, t_ixy xy)
{
	(void)xy;
	(void)button;
	vm->visu.notification.image_index = -1;
	vm->visu.buttons[OK_BUTTON].visible = 0;
	return (0);
}

static void	ft_apply_color_filter(SDL_Surface *surface, int color)
{
	SDL_Surface *s;

	s = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, color);
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_MOD);
	SDL_BlitSurface(s, NULL, surface, NULL);
	SDL_FreeSurface(s);
}

static int	ft_render_notification_panel(t_vm *vm, SDL_Rect notif_rect)
{
	SDL_BlitScaled(vm->visu.sdl.images[vm->visu.notification.image_index], NULL,
		vm->visu.sdl.w_surface, &notif_rect);
	ft_render_button(vm, &vm->visu.buttons[OK_BUTTON]);
	return (0);
}

int			ft_render_notification(t_vm *vm)
{
	SDL_Rect rect;

	if (vm->visu.notification.image_index != -1)
	{
		rect.w = vm->visu.center.notif_panel_w;
		rect.h = vm->visu.center.notif_panel_h;
		rect.x = vm->visu.center.notif_panel_left;
		rect.y = vm->visu.center.notif_panel_top;
		ft_apply_color_filter(vm->visu.sdl.w_surface, 0x44777777);
		ft_render_notification_panel(vm, rect);
	}
	return (0);
}
