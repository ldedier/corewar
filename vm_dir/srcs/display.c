/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/26 21:13:51 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_resize(t_vm *vm)
{
	if (vm->display & (1 << MSG_CYCLE))
		ft_printf("%s\nCycle to die is now %d"EOC, vm->col.resize, vm->c_to_die);
}

void		display_last_live(t_vm *vm, t_process *proc)
{
	if (vm->display & (1 << MSG_DEATH))
		ft_printf("\n%sProcess %d hasn't lived for %d cycles (CTD %d)"EOC,
				vm->col.death,
				proc->nb,
				vm->total_cycle - proc->live_cycle,
				vm->c_to_die);
}

void		display_cycle(t_vm *vm)
{
	if (vm->display & (1 << MSG_CYCLE))
		ft_printf("\n%sIt is now cycle %d"EOC, vm->col.cycle, vm->total_cycle);
}

void		display_registers(t_vm *vm)
{
	int		i;
	t_list	*proc_lst;

	proc_lst = vm->proc;
	ft_printf("*** DISPLAY REGISTERS ***\n\n");
	while (proc_lst && proc_lst->content)
	{
		i = -1;
		while (++i < REG_NUMBER && proc_lst->content)
			ft_printf("R%d: %d | ", i + 1, ((t_process *)proc_lst->content)->reg[i]);
		ft_printf("\n\n");
		proc_lst = proc_lst->next;
	}
}
