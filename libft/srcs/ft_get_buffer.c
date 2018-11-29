/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:55:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 18:44:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_empty_buffer(t_pf *pf)
{
	int		display;
	char	*toprint;

	display = 0;
	toprint = ft_get_buffer("", 0, &display, pf);
	if (pf->sprintf)
		ft_strcat(&(pf->buffer[ft_add_return(0)]), toprint);
	else
		write(pf->fd, toprint, display);
	ft_add_return(display);
	display = 1;
	ft_get_buffer("", 0, &display, pf);
}

char	*ft_get_buffer(const void *s, size_t n, int *display, t_pf *pf)
{
	static char	buffer[BUF_SIZE] = {0};
	static int	cursor = 0;

	if (*display)
		cursor = 0;
	else
	{
		if (cursor + n < BUF_SIZE)
		{
			ft_strncpy(&(buffer[(int)(cursor)]), s, n);
			cursor += n;
		}
		else
		{
			ft_empty_buffer(pf);
			if (pf->sprintf)
				ft_strncat(&(pf->buffer[ft_add_return(0)]), s, n);
			else
				write(pf->fd, s, n);
			ft_add_return(n);
		}
	}
	*display = cursor;
	return ((char *)(buffer));
}
