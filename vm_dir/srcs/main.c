/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/22 16:41:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
void __attribute__((destructor)) end();

void    end(void) //permet de mieux checker les leaks !
{
	ft_printf("destructor loop\n");
	while(1);
}
*/

int		main(int argc, char **argv, char **env)
{
	t_vm	vm;

	if (argc <= 1)
		error_exit_msg(USAGE);
	if (!check_type(argc, argv))
		error_exit_msg(WRG_FILE_TYPE);
	check_header();
	init_vm(&vm, argv, env);
	flags(&vm, argc, argv);
	if (read_files(&vm))
		error_exit_msg(RD_ERROR);
	dispatch_players_init(&vm);
	init_local_players(&vm);
	if (vm.client.active)
		return (process_client(&vm));
	if (vm.visu.active)
		return (process_visu(&vm));
	if (!init_processes(&vm))
		error_exit_msg(INIT_PROC_ERROR);
	while (vm.proc)
		process_cycle(&vm);
	display(&vm, NULL, MSG_WINNER);
	return (0);
}
