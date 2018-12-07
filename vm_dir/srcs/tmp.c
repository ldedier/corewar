/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:49:29 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 22:08:49 by emuckens         ###   ########.fr       */
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
/*
void		test_ins(t_vm *vm)
{
	static t_process	*proc;
	static char	ins[10] = {0x0b, 0x68, 0x01, 0x00, 0x0f, 0x01, 0x00};

	proc = (t_process *)ft_memalloc(sizeof(t_process) + (MAX_PLAYERS));
	set_processes(vm, &proc);
	ft_memmove((void *)vm->arena + 5, (void *)ins, 7);
	play(vm, (t_process **)&proc);
	//	t_arg arg[3] = {{2, 0}, {3, 0}, {2, 4}};
	//	ins_ld(vm, proc, arg);

}
*/
/*
void		set_processes(t_vm *vm, t_process **proc)
{
	int i;
	int op = 1;
	static char reg[REG_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	t_parameter arg[3];

	i = -1;
	(void)arg;
	while (++i < MAX_PLAYERS)
	{
		(*proc)[i].id = i;
		(*proc)[i].pc = i * (MEM_SIZE / MAX_PLAYERS); // verifier calcul
		(*proc)[i].cycle = 1;
		(*proc)[i].live = 1;

		ft_memmove((void *)(*proc)[i].reg, (void *)reg, REG_NUMBER);
		arg[0].value = i;
		arg[0].nb_bytes = 4;
		ft_memmove((void *)(vm->arena + i * 1024), (void *)&op, sizeof(char));
		ft_memmove((void *)(vm->arena + i * 1024 + 4), (void *)&arg[0].value, sizeof(int));

	}
}*/
