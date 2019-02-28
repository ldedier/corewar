/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_suite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:57:10 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/27 12:57:15 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_write(int fd, int value, int size)
{
	char	bytes[4];
	char	tmp;
	int		i;

	i = 0;
	while (i < size)
	{
		bytes[i] = (value >> (8 * i)) & 0xff;
		i++;
	}
	i = 0;
	while (i < size / 2)
	{
		tmp = bytes[i];
		bytes[i] = bytes[size - i - 1];
		bytes[size - i - 1] = tmp;
		i++;
	}
	return (write(fd, bytes, size));
}

void		ft_add_padding(int fd, int total_bytes)
{
	int		i;
	char	c;

	c = 0;
	i = 0;
	while ((i + total_bytes) % 4 != 0)
	{
		write(fd, &c, 1);
		i++;
	}
}
