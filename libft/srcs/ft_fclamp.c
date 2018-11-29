/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:21:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/31 15:22:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_fclamp(float min, float val, float max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	return (val);
}
