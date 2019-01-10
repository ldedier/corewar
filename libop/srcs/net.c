/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:10:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/10 17:41:36 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_memcpy_ret(void *dest, void *src, size_t size)
{
	ft_memcpy(dest, src, size);
	return (size);
}

void		ft_memcpy_recv(void *dest, void *src, int *index, size_t size)
{
	ft_memcpy(dest, &src[*index], size);
	*index += size;
}
