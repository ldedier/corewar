/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/25 13:51:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** dump_nb_cycles function is called when the -dump flag is used and stores the
** value given by the user in the [dump] component of the [t_vm] structure.
*/

static void	dump_nb_cycles(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	if (ft_strcmp("-dump", argv[*cur + 1]) == 0)
	{
		*cur += 2;
		if (*cur + 2 > argc)
			error_exit_msg(WRG_DUMP);
		i = 0;
		while (argv[*cur][i])
		{
			if (!(ft_strchr("-0123456789", argv[*cur][i])))
				error_exit_msg(WRG_DUMP);
			i++;
		}
		nb = ft_atoll(argv[*cur]);
		if (nb > 2147483647 || nb < 0)
			nb = -1;
		vm->dump = nb;
	}
}

/*
** add_player_n function adds a player to the list of contestants WITH a number
** specified with the [-n] flag.
*/

static void	add_player_n(t_vm *vm, int argc, char **argv, int *cur)
{
	int				i;

	if (*cur + 3 > argc)
		error_exit_msg(WRG_N_FLAG);
	i = -1;
	if (argv[*cur + 1][i + 1] == '-')
		i++;
	while (argv[*cur + 1][++i])
	{
		if (!(ft_strchr("0123456789", argv[*cur + 1][i])))
			error_exit_msg(WRG_N_FLAG);
	}
	vm->nb = ft_atoll(argv[*cur + 1]);
	if (vm->nb > 2147483647 || vm->nb < -2147483648)
		error_exit_msg(MAX_N_FLAG);
	i = -1;
	while (++i < vm->nb_players)
	{
		if (vm->player[i].num == vm->nb)
			error_exit_msg(WRG_P_NUM);
	}
	vm->player[vm->nb_players].num = vm->nb;
	vm->player[vm->nb_players].num_type = 1;
	*cur += 2;
}

/*
** add_player function adds a player to the list of contestants WITHOUT a
** number specified
*/

static int	add_player(t_vm *vm)
{
	int			i;
	static int	nb;

	i = -1;
	nb = -1;
	while (++i < vm->nb_players)
	{
		if (vm->player[i].num == nb)
		{
			--(nb);
			i = -1;
		}
	}
	return (nb);
}

/*
** flags function parses ./corewar 's arguments to check if there are any flags
** such as [-dump nbr-cycles] or [-n number], and then assigns a number to
** each player.
** Numbers attributed by default follow sequence -1, -2, -3, etc, unless number
** has been given to other player
*/

void		flags(t_vm *vm, int argc, char **argv)
{
	static int	cur;
	int			i;

	dump_nb_cycles(vm, argc, argv, &cur);
	while (++cur < argc)
	{
		if (argv[cur][0] == '-' && ft_isdigit(argv[cur][1]) && !(i = 0))
			while (ft_isdigit(argv[cur][++i]))
				vm->display = 10 * vm->display + (argv[cur][i] - '0');
		else if (!ft_strcmp("-v", argv[cur]))
			vm->visu.active = 1;
		else if (!ft_strcmp("-w", argv[cur]))
			corehub_port_and_address(vm, argc, argv, &cur);
		else
		{
			if (ft_strcmp("-n", argv[cur]) == 0)
				add_player_n(vm, argc, argv, &cur);
			else
				vm->player[vm->nb_players].num = add_player(vm);
			vm->player[vm->nb_players].cor_name = argv[cur];
			if (++vm->nb_players > MAX_PLAYERS)
				error_exit_msg(MAX_P_NUM);
		}
	}
}
