/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/04 17:13:22 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** update_nb_players updates the number of players currently in the arena
*/

void			update_nb_players(t_vm *vm)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
			res++;
		i++;
	}
	vm->nb_players = res;
}

/*
**init_vm function initializes our corewar VM's environment by setting all
**its parameters to their default value.
*/

void			init_vm(t_vm *vm, char **argv, char **env)
{
	int i;

	vm->c_to_die = CYCLE_TO_DIE;
	vm->files = argv;
	vm->win = 0;
	vm->dump = 0;
	vm->checks = MAX_CHECKS;
	vm->live.nb = 0;
	vm->live.total_pl = 0;
	vm->proc = NULL;
	vm->client.active = 0;
	vm->client.port = 0;
	vm->visu.active = 0;
	//	vm->cycle = 0;
	ft_bzero(vm->color, MAX_PL_COLOR);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_strlcat(vm->color, init_color_ref(env), MAX_PL_COLOR);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		vm->player[i].color.value = NULL;
		i++;
	}
}

t_list			*add_process(t_vm *vm, int index, int start)
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	process->player = &vm->player[index];
	process->pc = start;
	process->reg[0] = process->player->num;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}

int				init_processes(t_vm *vm)
{
	int i;
	int	index;
	int start;

	i = -1;
	index = 1;
	while (++i < MAX_PLAYERS)
	{
		start = (MEM_SIZE / vm->nb_players) * (index - 1);
		if (vm->player[i].relevant && ++index && !add_process(vm, i, start))
			return (0);
	}
	vm->live.last_pl = (t_process *)(vm->proc->content);
	return (1);
}

/*
**dispatch_players function sends each player to their respective starting
**point in the arena and initializes processes for each player.
*/

void			dispatch_players_init(t_vm *vm)
{
	int			index;
	int			i;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
	{
		set_color(&vm->player[i], vm->color);
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
	}
}

int				ft_get_potential_num(int player_num)
{
	if (player_num == INT_MAX)
		return (INT_MIN);
	else
		return (player_num + 1);
	return (0);
}

void			ft_set_numbers(t_player players[MAX_PLAYERS], t_player *player)
{
	int i;
	int j;
	int found;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].relevant && player != &players[i])
		{
			player->num = ft_get_potential_num(players[i].num);
			found = 1;
			j = -1;
			while (++j < MAX_PLAYERS)
			{
				if (i != j && players[j].relevant && &players[j] != player &&
						player->num == players[j].num)
				{
					found = 0;
					break ;
				}
			}
			if (found)
				return ;
		}
	}
}

/*
**dispatch_players function sends each player to their respective starting
**point in the arena and initializes processes for each player.
*/

void			dispatch_players(t_vm *vm, t_player *player)
{
	int			index;
	int			i;
	int			j;
	int			start;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	i = -1;
	index = 0;
	while (++i < MAX_PLAYERS)
	{
		if (set_color(&vm->player[i], vm->color) && player != &vm->player[i])
			ft_set_numbers(vm->player, &(vm->player[i]));
		if (vm->player[i].relevant && ++index && (j = -1))
		{
			start = (MEM_SIZE / vm->nb_players) * (index - 1);
			while (++j < vm->player[i].algo_len)
			{
				vm->metarena[start + j].color_index = vm->player[i].color.index;
				*(vm->arena + start + j) = vm->player[i].algo[j];
			}
		}
	}
}
