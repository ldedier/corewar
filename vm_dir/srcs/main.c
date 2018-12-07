/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 22:44:37 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;
	t_process	*all_process;

	if (argc <= 1)
		error_exit_msg(USAGE);
	if (!check_type(argc, argv))
		error_exit_msg(WRG_FILE_TYPE);
	init_vm(&vm, argv);
	flags(&vm, argc, argv);
	read_files(&vm);
//	all_process = (t_process *)ft_memalloc(sizeof(t_process) * (vm.nb_players));
	parse(&vm);
//	if (vm.client.active)
//		return (process_client(&vm));
	dispatch_players(&vm, (t_process **)&all_process);
//	ft_printf("player 2 starts at %d\n", all_process[0].pc);
//	play(&vm, (t_process **)&all_process);
//	test(vm);
	return (0);
}
