/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/21 16:56:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_print_usage(char *name)
{
	ft_printf("%s [port (ex: 3001)]\n", name);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	t_server server;

	if (SDLNet_Init() == -1)
		return (ft_error());
	if (ft_init_server(argc, argv, &server, env))
		return (1);
	if (ft_parse_player_folder(PATH"/cores", &server.players))
		return (1);
	if (ft_attribute_scores_init(&server))
		return (1);
	ft_printf(GREEN"server successfuly deployed on port %d!\n\n"EOC,
			server.port);
	ft_printf("%s\n", ACTIVITY_SRCH);
	if (ft_process_server(&server))
		return (1);
	return (0);
}
