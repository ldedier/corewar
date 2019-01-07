/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/07 17:28:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
		return (1);
	dispatch_players_init(&vm);
	init_local_players(&vm);
	if (vm.client.active)
		return (process_client(&vm));
	for (int i = 0; i < MAX_PLAYERS; ++i)
		ft_printf("player %d name= %s\n", i, vm.player[i].name);
//	ft_printf("player 2 starts at %d\n", all_process[0].pc);
//	play(&vm, (t_process **)&all_process);
	if (vm.visu.active)
		return (process_visu(&vm));
	if (!init_processes(&vm))
		return (1);
	play(&vm);
	display_arena((unsigned char *)vm.arena);
//	test(vm);
	return (0);
}
