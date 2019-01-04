/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_play_footer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:00:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/04 00:03:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_winner(t_vm *vm)
{
	(void)vm;
	return (0);
}

int		ft_render_play_footer(t_vm *vm)
{
	if (ft_render_winner(vm))
		return (1);
	if (ft_render_button(vm, &vm->visu.buttons[BACK_BUTTON]))
		return (1);
	return (0);
}
