/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 21:19:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t	ft_memcpy_ret(void *dest, void *src, size_t size)
{
	ft_memcpy(dest, src, size);
	return (size);
}

int		ft_send_protected(TCPsocket socket, void *data, size_t size)
{
	if (SDLNet_TCP_Send(socket, data, size) < (int)size)
		return (1);
	return (0);
}

int		ft_error(void)
{
	ft_printf("%s\n", SDL_GetError());
	return (1);
}
