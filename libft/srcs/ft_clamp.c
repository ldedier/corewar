/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:39:28 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/18 19:40:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_clamp(int min, int val, int max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	return (val);
}
