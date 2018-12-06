/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:49:29 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/05 22:35:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_arena(t_arena *arena)
{
	int		cur;

	cur = -1;
	while (++cur < MEM_SIZE)
	{
		ft_printf("%0*x ", 2, arena[cur]);
		if (cur >= 2 && !((cur + 1) % 64))
			ft_printf("\n");
		else if (cur >= 2 && !((cur + 1) % 8))
			ft_printf("| ");
	}
}

int			check_resize_cycle(t_vm *vm, int *cycle)
{
	if (vm->nb_live >= NBR_LIVE)
	{
		vm->max_checks = 0;
		vm->nb_live = 0;
		vm->c_to_die -= CYCLE_DELTA;
	}
	else if (vm->max_checks >= MAX_CHECKS)
	{
		vm->max_checks = 0;
		vm->c_to_die -= CYCLE_DELTA;
	}
	else if (++vm->max_checks) 
		return (0);
	*cycle = 0;
	return (1);
}

void		test_ins(t_vm *vm)
{
	static t_process	*proc;
	static char	ins[10] = {0x0b, 0x68, 0x01, 0x00, 0x0f, 0x01, 0x00};

	proc = (t_process *)ft_memalloc(sizeof(t_process) + (MAX_PLAYERS));


	t_op tab[NB_INSTRUCTIONS + 1];
	set_optab((t_op **)&tab);
	set_processes(vm, &proc);
	ft_memmove((void *)vm->arena + 5, (void *)ins, 7);
	play(vm, (t_process **)&proc, tab);
//	t_arg arg[3] = {{2, 0}, {3, 0}, {2, 4}};
//	ins_ld(vm, proc, arg);

}