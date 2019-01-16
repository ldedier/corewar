/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_of_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 21:09:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/15 21:10:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int     out_of_atlas_range(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < ATLAS_MIN || str[i] > ATLAS_MAX)
			return (1);
		i++;
	}
	return (0);
}
