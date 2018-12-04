/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:49:29 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 21:32:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		display_arena(t_arena *arena)
{
	int		cur;
	char	*ptr;

	cur = 0;
	ptr = (char *)arena;
	while (++cur < MEM_SIZE)
	{
		ft_printf("%0*x ", 2, arena[cur]);
		if (!(cur % 64))
			ft_printf("\n");
		else if (!(cur % 8))
			ft_printf("| ");
	}
}

int			resize_cycle(t_vm *vm)
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
	return (1);
}

void		test_ins(t_vm *vm, t_process *proc)
{
	static char reg[REG_NUMBER] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160};
	static int	cycles;
	int			opcode;

	t_op tab[17];

	set_optab((t_op **)&tab);
	ft_memmove(proc->reg, reg, REG_NUMBER);
	t_arg arg[3] = {{2, 0}, {3, 0}, {2, 4}};
	cycles = 0;
	ins_ld(vm, proc, arg);

	if (cycles)
	{
		--cycles;
		return ;
	}	
	if (!(opcode = get_instruction(vm, tab, proc)))
	{
		++cycles;
		proc->pc = (proc->pc == MEM_SIZE - 1 ? 0 : proc->pc + 1);
	}
	else
		cycles += tab[opcode].nb_cycles;
}
