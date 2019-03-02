/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:25:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/02 20:49:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handle_kill(int signal)
{
	(void)signal;
	exit(reset_shell(1));
}

void	init_signals(void)
{
	signal(SIGINT, handle_kill);
	signal(SIGHUP, handle_kill);
	signal(SIGTERM, handle_kill);
	signal(SIGABRT, handle_kill);
	signal(SIGALRM, handle_kill);
	signal(SIGQUIT, handle_kill);
	signal(SIGTSTP, handle_kill);
	signal(SIGSTOP, handle_kill);
	signal(SIGCONT, handle_kill);
}
