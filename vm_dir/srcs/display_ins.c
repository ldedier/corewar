/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:05:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/11 19:53:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_proc_ins(t_vm *vm, t_process *proc)
{
	t_parameter *param;
	int			i;

	if (!(vm->display.code & (1 << MSG_INS)) || vm->visu.active)
		return ;
	i = -1;
	ft_printf("\nP %4d | %s", proc->nb, proc->pending_ins.op->instruction_name);
	while (++i < proc->pending_ins.op->nb_params)
	{
		param = &proc->pending_ins.params[i];
		if (param->retrieval_mode)
			ft_printf(" %d", param->dest_value);
		else
			ft_printf(" %s%d", param->type == T_REG ? "r" : "", param->value);
	}
}

void		display_move(t_vm *vm, t_process *proc)
{
	int				i;
	int				len;
	unsigned char	c;

	len = ft_abs(proc->ins_bytelen);
	if (!(vm->display.code & (1 << MSG_MOVE)) || vm->visu.active)
		return ;
	if (proc->pending_ins.op->opcode == ZJMP && proc->carry)
		return ;
	proc->pc = mod(proc->pc, MEM_SIZE);
	ft_printf("\nADV %d (0x%04x -> 0x%04x) ", len, proc->pc, (proc->pc + len));
	i = -1;
	while (++i < len)
	{
		c = (unsigned char)(vm->arena[mod(proc->pc + i, MEM_SIZE)]);
		ft_printf("%02x ", c);
	}
}
