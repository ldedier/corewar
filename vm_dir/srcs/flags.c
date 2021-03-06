/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2019/03/11 18:28:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			corehub_port_and_address(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	vm->client.active = 1;
	vm->visu.active = 1;
	if (*cur + 2 > argc)
		return (error_exit_msg(vm, INSUF_INFO_CH));
	*cur += 1;
	vm->client.server_address = argv[*cur];
	*cur += 1;
	i = 0;
	while (argv[*cur][i])
	{
		if (!(ft_strchr("0123456789", argv[*cur][i])))
			return (error_exit_msg(vm, INVALID_PORT));
		i++;
	}
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647)
		return (error_exit_msg(vm, INVALID_PORT));
	vm->client.port = nb;
	return (SUCCESS);
}

/*
** dump_nb_cycles function is called when the -dump flag is used and stores the
** value given by the user in the [dump] component of the [t_vm] structure.
*/

static int	dump_nb_cycles(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;

	*cur += 1;
	if (*cur + 1 > argc)
		return (FAILURE);
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647 || nb < -1 || vm->visu.active)
		nb = -1;
	vm->dump = nb;
	return (SUCCESS);
}

/*
** mng_players static function manages the case where the current argument
** describes a player
*/

static int	mng_players(t_vm *vm, int argc, char **argv, int *cur)
{
	if (ft_strcmp("-n", argv[*cur]) == 0)
		add_player_n(vm, argc, argv, cur);
	else
		vm->player[vm->nb_players].num = add_player(vm);
	vm->player[vm->nb_players].cor_name = argv[*cur];
	if (++vm->nb_players > MAX_PLAYERS)
		return (error_exit_msg(vm, MAX_P_NUM));
	return (0);
}

/*
** flags_bis is the second part of the flags function because of 42's norm
*/

static int	flags_bis(t_vm *vm, int argc, char **argv, int *cur)
{
	if (!ft_strcmp("-c", argv[*cur]))
		vm->display.status = ON;
	else if (!ft_strcmp("-a", argv[*cur]))
		vm->display.code |= (1 << MSG_AFF);
	else if (!ft_strcmp("-v", argv[*cur]))
	{
		vm->visu.active = 1;
		vm->dump = -1;
	}
	else if (mng_players(vm, argc, argv, cur))
		return (FAILURE);
	return (0);
}

/*
** flags function parses ./corewar 's arguments to check if there are any flags
** such as [-dump nbr-cycles] or [-n number], and then assigns a number to
** each player.
** Numbers attributed by default follow sequence -1, -2, -3, etc, unless number
** has been given to other player
*/

int			flags(t_vm *vm, int argc, char **argv)
{
	static int	cur;
	int			i;

	while (++cur < argc)
	{
		if (!ft_strcmp("-dump", argv[cur]))
		{
			if (dump_nb_cycles(vm, argc, argv, &cur))
				return (error_exit_msg(vm, WRG_DUMP));
		}
		else if (argv[cur][0] == '-' && ft_isdigit(argv[cur][1]) && !(i = 0))
		{
			while (ft_isdigit(argv[cur][++i]))
				vm->display.code = 10 * vm->display.code + (argv[cur][i] - '0');
		}
		else if (!ft_strcmp("-w", argv[cur]))
		{
			if (corehub_port_and_address(vm, argc, argv, &cur))
				return (FAILURE);
		}
		else if (flags_bis(vm, argc, argv, &cur))
			return (FAILURE);
	}
	return (SUCCESS);
}
