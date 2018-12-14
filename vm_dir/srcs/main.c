/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/14 17:59:16 by emuckens         ###   ########.fr       */
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
//	parse(&vm); //now in read_files
//	all_process = (t_process *)ft_memalloc(sizeof(t_process) * (vm.nb_players));
//	dispatch_players(&vm, (t_process **)&all_process);
	dispatch_players(&vm);
	ft_memcpy(vm.local_player, vm.player, sizeof(vm.player));
	if (vm.client.active)
		return (process_client(&vm));
//	ft_printf("player 2 starts at %d\n", all_process[0].pc);
//	play(&vm, (t_process **)&all_process);
	if (vm.visu.active)
		return (process_visu(&vm));
	play(&vm);
	display_arena((unsigned char *)vm.arena);
//	test(vm);
	return (0);
}
