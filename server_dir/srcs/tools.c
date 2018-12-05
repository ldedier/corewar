/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/05 17:57:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
