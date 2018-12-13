/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/13 19:04:47 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc <= 1)
		error_exit_msg(USAGE);
	if (!check_type(argc, argv))
		error_exit_msg(WRG_FILE_TYPE);
	check_header();
	init_vm(&vm, argv);
	flags(&vm, argc, argv);
	read_files(&vm);
//	if (vm.client.active)
//		return (process_client(&vm));
//	if (vm.visu.active)
//		return (process_visu(&vm));

	dispatch_players(&vm);
	play(&vm);
	display_arena((unsigned char *)vm.arena);
//	test(vm);
	return (0);
}
