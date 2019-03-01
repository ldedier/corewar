/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/01 22:21:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void __attribute__((destructor)) end();

void    end(void) //permet de mieux checker les leaks !
{
	ft_printf("destructor loop\n");
	while(1);
}


int		main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm, argv);
	if (argc <= 1)
		return (error_exit_msg(&vm, USAGE));
	if (!check_type(argc, argv))
		return (error_exit_msg(&vm, WRG_FILE_TYPE));
	check_header(&vm);
	if (flags(&vm, argc, argv))
		return (FAILURE);
	set_colors_term(&vm);
	if (read_files(&vm))
		return (error_exit_msg(&vm, RD_ERROR));
	dispatch_players_init(&vm);
	if (vm.client.active)
		return (process_client(&vm));
	if (vm.visu.active)
		return (process_visu(&vm));
	if (!init_processes(&vm))
		return (error_exit_msg(&vm, INIT_PROC_ERROR));
	while (vm.proc)
		play_one_cycle(&vm);
	display_winner(&vm);
	clear_vm(&vm);
	return (0);
}
