/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:49:29 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/05 18:03:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_arena(unsigned char *arena)
{
	int		cur;

	cur = -1;
	while (++cur < MEM_SIZE)
	{
		ft_printf("%0*x ", 2, (unsigned char)arena[cur]);
		if (cur >= 2 && !((cur + 1) % 64))
			ft_printf("\n");
		else if (cur >= 2 && !((cur + 1) % 8))
			ft_printf("| ");
	}
}
