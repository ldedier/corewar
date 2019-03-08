/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/07 18:02:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void __attribute__((destructor)) end();

void    end(void) //permet de mieux checker les leaks !
{
//	ft_printf("destructor loop\n");
//	while(1);
}

static int		valid_input(int argc, char **argv, t_vm *vm)
{
	if (!check_type(argc, argv))
		return (error_exit_msg(vm, WRG_FILE_TYPE));
	if (!check_header())
		return (error_exit_msg(vm, ERR_HEADER));
	if (!flags(vm, argc, argv))
		return (error_exit_msg(vm, WRG_DUMP));
	set_colors_term(vm);
	if (read_files(vm))
		return (error_exit_msg(vm, RD_ERROR));
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm, argv);
	if (argc <= 1)
		return (error_exit_msg(&vm, USAGE));
	if (valid_input(argc, argv, &vm) == FAILURE)
		return (FAILURE);
	dispatch_players_init(&vm);
	if (vm.client.active)
		return (process_client(&vm));
	if (vm.visu.active)
		return (process_visu(&vm));
	if (!init_processes(&vm))
		return (error_exit_msg(&vm, INIT_PROC_ERROR));
	while (vm.proc)
		if (play_one_cycle(&vm) == FAILURE)
			return (error_exit_msg(&vm, ERR_MALLOC));
	display_winner(&vm);
	clear_vm(&vm);
	return (SUCCESS);
}
