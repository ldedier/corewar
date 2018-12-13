/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/13 19:06:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**init_vm function initializes our corewar VM's environment by setting all
**its parameters to their default value.
*/

void					init_vm(t_vm *vm, char **argv)
{
	int		i;

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
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i] = 0;
		i++;
	}
	ft_strcpy(vm->color, "RxLxYxBxyxyx");
	set_colors(vm->color);
}

t_list	*add_process(t_vm *vm, char *name, int start, int num)
{
	static char	color;
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	ft_printf("colindex = %d\n", color);
	process->colindex = (color++) % MAX_PL_COL;
	process->pc = start;
	ft_strcpy(process->name, name);
	process->id = num; // revoir utilisation et valeur
	process->reg[0] = num;
	if (ft_add_to_list_ptr(&vm->proc, (void *)process, sizeof(process)))
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
	int		start;
	char		*algo;

	nb = 0;
	while (nb < vm->nb_players)
	{
		start = (MEM_SIZE / vm->nb_players) * nb;
		algo = vm->player[nb].algo;
		if (!add_process(vm, vm->player[nb].name, start, vm->player[nb].num))
			return (-1);
		i = 0;
		while (i < vm->player[nb].algo_len)
		{
			vm->arena[start] = algo[i];
			i++;
			start++;
		}
		nb++;
	}
	vm->live.last_pl = vm->player[vm->nb_players - 1].num;;
	return (0);
}
