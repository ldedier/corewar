/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/14 00:21:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** update the number of players currently in the arena
*/

void	update_nb_players(t_vm *vm)
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

void					init_vm(t_vm *vm, char **argv)
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
	vm->cycle = 0;
	ft_bzero(vm->arena, MEM_SIZE);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].relevant = 0;
		i++;
	}
	ft_strcpy(vm->color, "xRWMGCgw"); // sera gere differemment par la suite
	set_colors(vm->color);
}

t_list	*add_process(t_vm *vm, char *name, int nb, int start, int num) //need name?
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	process->colindex = (nb + 1) % MAX_PL_COL; //quick fix, needs rework
	process->pc = start;
	ft_strcpy(process->name, name);
	process->id = num;
	process->reg[0] = num;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(t_process)))
		return (NULL);
	return (vm->proc);
}

/*
**dispatch_players function sends each player to their respective starting
**point in the arena and initializes processes for each player.
*/

int		dispatch_players(t_vm *vm)
{
	int		nb;
	int		i;
	int		j;
	int		start;
	char	*algo;

	update_nb_players(vm);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->metarena, sizeof(vm->metarena));
	ft_lstdel_value(&vm->proc);
	i = 0;
	nb = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].relevant)
		{
			start = (MEM_SIZE / vm->nb_players) * nb;
			algo = vm->player[i].algo;
			if (!add_process(vm, vm->player[i].name, nb, start, vm->player[i].num))
				return (-1);
			vm->player[i].color_index =
				((t_process *)(vm->proc->content))->colindex;
			j = 0;
			while (j < vm->player[i].algo_len)
			{
				vm->metarena[start].color_index = ((t_process *)(vm->proc->content))->colindex;
				vm->arena[start] = algo[j];
				j++;
				start++;
			}
			nb++;
		}
		i++;
	}
	vm->live.last_pl = vm->player[vm->nb_players - 1].num;
	return (0);
}
