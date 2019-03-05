/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_buttons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:43:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 19:58:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_process_render_button(t_vm *vm, SDL_Rect rect,
		SDL_Surface *surface, t_vscrollbar *vscrollbar)
{
	if (vscrollbar == NULL)
	{
		if (SDL_BlitScaled(surface, NULL,
					vm->visu.sdl.w_surface, &rect) < 0)
			return (ft_net_error());
		return (0);
	}
	else
		return (ft_blit_scaled_scrollbar(&vm->visu.sdl,
				surface, rect, *vscrollbar));
}

int		ft_render_upload_button(t_vm *vm, t_button *this)
{
	int	dropped_player;

	dropped_player = 0;
	if (vm->visu.drop_container.player == &vm->client.upload_player)
		dropped_player = 1;
	if ((vm->visu.drag_container.drag_enum == DRAG_PLAYER && dropped_player)
			|| (vm->client.upload_player.relevant == 1
				&& (vm->visu.drag_container.drag_enum != DRAG_PLAYER
					|| vm->visu.drag_container.drag_union.drag_player.player
					!= &vm->client.upload_player)))
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[UL], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[UL_DISABLED], this->vscrollbar));
}

int		ft_render_trash_button(t_vm *vm, t_button *this)
{
	if (this->enabled)
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[TRASH], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[TRASH_DISABLED], this->vscrollbar));
}

int		ft_render_download_button(t_vm *vm, t_button *this)
{
	if (!this->button_union.client_slot->on_disk)
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[DL], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[DL_DISABLED], this->vscrollbar));
}

int		ft_render_switch_button(t_vm *vm, t_button *this)
{
	if (vm->visu.local_type == LOCAL_LOCAL)
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[SWITCH_1], this->vscrollbar));
	else
		return (ft_process_render_button(vm, this->rect,
					vm->visu.sdl.images[SWITCH_2], this->vscrollbar));
}
