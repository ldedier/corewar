/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instru_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:43:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 18:44:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			getval_mod(char *arena, int index, int nb_bytes, int modulo)
{
	unsigned int	i;
	int				val;

	i = 0;
	val = 0;
	val |= arena[(index + i) % modulo];
	while (++i < (unsigned int)nb_bytes)
	{
		val <<= 8;
		val |= (unsigned char)arena[(index + i) % modulo];
	}
	return (val);
}
