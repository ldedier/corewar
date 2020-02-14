/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2020/02/14 15:25:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		print_usage(t_vm *vm)
{
	clear_vm(vm);
	ft_dprintf(2, "Usage: ./corewar [-dump nb] [-nb|-v|-w|-c|-a] [-n nb]");
	ft_dprintf(2, " <champion1.cor> <...>\n##################################");
	ft_dprintf(2, "####################################################\n");
	ft_dprintf(2, "\t-dump nb\t: Dumps memory after nb cycles then exits\n");
	ft_dprintf(2, "\t-v\t\t: SDL2 Visual output mode\n");
	ft_dprintf(2, "\t-w\t\t: SDL2 Network mode\n");
	ft_dprintf(2, "\t-c\t\t: Colorful mode\n");
	ft_dprintf(2, "\t-a\t\t: Prints output of each \"aff\"\n");
	ft_dprintf(2, "\t-n nb\t\t: Attributes number nb to next player\n");
	ft_dprintf(2, "\t-nb\t\t: Verbosity levels, can be added together");
	ft_dprintf(2, " to enable several\n\t\t\t\t-0 : Show only essentials");
	ft_dprintf(2, "\n\t\t\t\t-1 : Show lives\n\t\t\t\t-2 : Show ");
	ft_dprintf(2, "cycles\n\t\t\t\t-4 : Show operations\n\t\t\t\t");
	ft_dprintf(2, "-8 : Show deaths\n\t\t\t\t-16 : Show PC movements\n#######");
	ft_dprintf(2, "#########################################################");
	ft_dprintf(2, "#######################\n");
	return (1);
}

static int		valid_input(int argc, char **argv, t_vm *vm)
{
	if (!check_type(argc, argv))
		return (error_exit_msg(vm, WRG_FILE_TYPE));
	if (!check_header())
		return (error_exit_msg(vm, ERR_HEADER));
	if (flags(vm, argc, argv))
		return (FAILURE);
	set_colors_term(vm);
	if (read_files(vm))
		return (error_exit_msg(vm, RD_ERROR));
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm, argv);
	if (argc <= 1)
		return (print_usage(&vm));
	if (valid_input(argc, argv, &vm) == FAILURE)
		return (FAILURE);
	dispatch_players_init(&vm);
	if (vm.client.active)
		return (process_client(&vm));
	if (vm.visu.active)
		return (process_visu(&vm));
	if (init_processes(&vm))
		return (error_exit_msg(&vm, INIT_PROC_ERROR));
	while (vm.proc)
		if (play_one_cycle(&vm) == FAILURE)
			return (error_exit_msg(&vm, ERR_MALLOC));
	display_winner(&vm);
	clear_vm(&vm);
	return (SUCCESS);
}
