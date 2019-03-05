/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:20:21 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/02 16:29:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_players function initializes each player's structures' parameters to
** their default value
*/

void			init_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = 1;
		vm->player[i].last_live_cycle = 0;
		vm->player[i].nb_proc = 0;
		vm->player[i].num_type = -1;
		ft_bzero(vm->player[i].aff_buf, MAX_AFF_LEN + 1);
	}
}

/*
** update_nb_players updates the number of players currently in the arena
*/

void			update_nb_players(t_vm *vm)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			res++;
	}
	vm->nb_players = res;
}

/*
** store each player data to their respective starting point in the arena
** NB!!: arena and metarena MUST follow each other in structure declaration, for
** correct bzero
*/

void			dispatch_players_init(t_vm *vm)
{
	static int	index;
	static int	i = -1;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_printf("%s", vm->visu.active ? "" : "Introducing contestants...");
	while (++i < MAX_PLAYERS)
	{
		set_color_sdl(vm, &vm->player[i]);
		if (vm->player[i].relevant && ++index)
		{
			j = -1;
			display_player_intro(vm, &vm->player[i]);
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
		vm->local_player[i] = vm->player[i];
		vm->local_player[i].color.value = 1;
		vm->local_player[i].num = vm->nb;
	}
}

/*
** add_player_n function adds a player to the list of contestants WITH a number
** specified with the [-n] flag.
*/

int				add_player_n(t_vm *vm, int argc, char **argv, int *cur)
{
	int				i;

	if (*cur + 3 > argc)
		return (error_exit_msg(vm, WRG_N_FLAG));
	i = -1;
	if (argv[*cur + 1][i + 1] == '-')
		i++;
	while (argv[*cur + 1][++i])
	{
		if (!(ft_strchr("0123456789", argv[*cur + 1][i])))
			return (error_exit_msg(vm, WRG_N_FLAG));
	}
	vm->nb = ft_atoll(argv[*cur + 1]);
	if (vm->nb > 2147483647 || vm->nb < -2147483648)
		return (error_exit_msg(vm, MAX_N_FLAG));
	i = -1;
	while (++i < vm->nb_players)
	{
		if (vm->player[i].num == vm->nb)
			return (error_exit_msg(vm, WRG_P_NUM));
	}
	vm->player[vm->nb_players].num = vm->nb;
	vm->player[vm->nb_players].num_type = 1;
	*cur += 2;
	return (0);
}

/*
** add_player function adds a player to the list of contestants WITHOUT a
** number specified
*/

int				add_player(t_vm *vm)
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
