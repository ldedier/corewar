/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:57:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/17 17:21:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_send_flag(t_server *server, int client_index, t_flag flag)
{
	if (ft_send_protected(server->client_sockets[client_index].socket,
				&flag, sizeof(t_flag)))
		return (1);
	return (0);
}

int		ft_send_rejection(TCPsocket socket)
{
	t_flag flag;

	flag = SERVER_FULL;
	if (ft_send_protected(socket, &flag, sizeof(flag)))
		return (1);
	return (0);
}

int		ft_send_deconnexion(TCPsocket socket, t_player_number player_number)
{
	t_flag	flag;
	char	*data;
	int		size;

	size = 0;
	flag = DISCONNECTION;
	if (!(data = (char *)malloc(sizeof(t_flag) + sizeof(t_player_number))))
		return (1);
	size += ft_memcpy_ret(&(data[size]), &flag, sizeof(flag));
	size += ft_memcpy_ret(&(data[size]), &player_number, sizeof(player_number));
	if (ft_send_protected(socket, data, size))
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}
