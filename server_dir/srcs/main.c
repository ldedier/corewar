/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/06 20:59:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static struct termios  g_term_init;

void __attribute__((destructor)) end();
void	end(void) //permet de mieux checker les leaks !
{
//	ft_printf("destructor loop\n");
//	while(1);
}

int		ft_print_usage(char *name)
{
	ft_printf("%s [port (ex: 3001)]\n", name);
	return (1);
}

int		reset_shell(int ret)
{
	if (tcsetattr(0, TCSADRAIN, &g_term_init) == -1)
	{
		ft_dprintf(2, "could not modify this terminal attributes\n");
		return (-1);
	}
	return (ret);
}

int		init_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
	{
		ft_dprintf(2, "could not copy the terminal attributes\n");
		return (1);
	}
	if (tcgetattr(0, &g_term_init) == -1)
	{
		ft_dprintf(2, "could not copy the terminal attributes\n");
		return (1);
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= ISIG;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		ft_dprintf(2, "could not modify this terminal attributes\n");
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_server server;

	if (SDLNet_Init() == -1)
		return (ft_error());
	if (init_term())
		return (1);
	if (ft_init_server(argc, argv, &server))
		return (exit_server(&server, 1));
	if (ft_parse_player_folder(PATH"/cores", &server.players))
		return (exit_server(&server, 1));
	if (ft_attribute_scores_init(&server))
		return (exit_server(&server, 1));
	ft_printf(GREEN"server successfuly deployed on port %d!\n\n"EOC,
			server.port);
	ft_printf("%s\n", ACTIVITY_SRCH);
	if (ft_process_server(&server))
		return (exit_server(&server, 1));
	return (exit_server(&server, 1));
}
