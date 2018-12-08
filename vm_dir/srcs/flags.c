/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 17:36:05 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**dump_nb_cycles function is called when the -dump flag is used and stores the
**value given by the user in the [dump] component of the [t_vm] structure.
*/

static void	dump_nb_cycles(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	*cur += 1;
	if (*cur + 2 > argc)
		error_exit_msg(WRG_DUMP);
	i = 0;
	while (argv[*cur][i])
	{
		if (!(ft_strchr("0123456789", argv[*cur][i])))
			error_exit_msg(WRG_DUMP);
		i++;
	}
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647)
		error_exit_msg(MAX_DUMP);
	vm->dump = nb;
	*cur += 1;
}

/*
**add_player_n function adds a player to the list of contestants WITH a number
**specified with the [-n] flag.
*/

static void	add_player_n(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	if (*cur + 3 > argc)
		error_exit_msg(WRG_N_FLAG);
	i = 0;
	if (argv[*cur + 1][i] == '-')
		i++;
	while (argv[*cur + 1][i])
	{
		if (!(ft_strchr("0123456789", argv[*cur + 1][i])))
			error_exit_msg(WRG_N_FLAG);
		i++;
	}
	nb = ft_atoll(argv[*cur + 1]);
	if (nb > 2147483647 || nb < -2147483648)
		error_exit_msg(MAX_N_FLAG);
	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->player[i].num == nb)
			error_exit_msg(WRG_P_NUM);
		i++;
	}
	vm->player[vm->nb_players].num = nb;
	*cur += 2;
	vm->player[vm->nb_players].cor_name = argv[*cur];
}

/*
**add_player_2 function is used by add_player function to determine which
**smallest unused number it can assign to the current player.
*/

static int	add_player_2(t_vm *vm, int min)
{
	int	i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (min == vm->player[i].num)
		{
			min++;
			i = 0;
		}
		else
			i++;
	}
	return (min);
}

/*
**add_player function adds a player to the list of contestants WITHOUT a
**number specified with the [-n] flag.
*/

static void	add_player(t_vm *vm, char **argv, int *cur, int nb_pl)
{
	int	nb;
	int	i;
	int	min;

	if (nb_pl == 0)
		nb = 1;
	else
	{
		min = vm->player[0].num;
		i = 1;
		while (i < nb_pl)
		{
			if (min > vm->player[i].num)
				min = vm->player[i].num;
			i++;
		}
		min++;
		nb = add_player_2(vm, min);
	}
	vm->player[nb_pl].num = nb;
	vm->player[nb_pl].cor_name = argv[*cur];
}

/*
**flags function parses ./corewar 's arguments to check if there are any flags
**such as [-dump nbr-cycles] or [-n number], and then assigns a number to
**each player.
*/

void		flags(t_vm *vm, int argc, char **argv)
{
	int cur;

	cur = 1;
	vm->nb_players = 0;
	if (ft_strcmp("-dump", argv[cur]) == 0)
		dump_nb_cycles(vm, argc, argv, &cur);
	while (cur < argc)
	{
/*		if (!ft_strcmp("-v", argv[cur]))
			vm->visu.active = 1;
		else if (!ft_strcmp("-corehub", argv[cur]))
			corehub_port_and_address(vm, argc, argv, &cur);
		else
		{*/
			if (ft_strcmp("-n", argv[cur]) == 0)
				add_player_n(vm, argc, argv, &cur);
			else
				add_player(vm, argv, &cur, vm->nb_players);
			vm->nb_players += 1;
			if (vm->nb_players > MAX_PLAYERS)
				error_exit_msg(MAX_P_NUM);
		cur++;
	}
}
