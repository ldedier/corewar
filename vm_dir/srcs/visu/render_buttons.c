/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_buttons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:43:09 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/30 20:40:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_upload_button(t_vm *vm, t_button *this)
{
	if ((vm->visu.drag_container.drag_enum == DRAG_PLAYER  &&
			vm->visu.drop_container.player == &vm->client.upload_player) ||
			(vm->client.upload_player.relevant == 1 && 
			 (vm->visu.drag_container.drag_enum != DRAG_PLAYER ||
			  vm->visu.drag_container.drag_union.drag_player.player
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