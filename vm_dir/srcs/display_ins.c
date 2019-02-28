/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:05:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/28 15:55:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_proc_ins(t_vm *vm, t_process *proc)
{
	int i;
	int arg_type;
	int	val;

	if (!(vm->display.code & (1 << MSG_INS)))
		return ;
	i = -1;
	ft_printf("\nP %4d | %s", proc->nb, proc->pending_ins.op->instruction_name);
	while (++i < proc->pending_ins.op->nb_params)
	{
		if (proc->pending_ins.params[i].retrieval_mode)
		{
			ft_printf(" %d", proc->pending_ins.params[i].dest_value);
//			if (proc->pending_ins.op->opcode == LIVE)
//				ft_printf("coucou");
		}
		else
		{
			val = proc->pending_ins.params[i].value;
			arg_type = proc->pending_ins.params[i].type;
			if (!(proc->pending_ins.op->opcode == ST && i == 1)) // pas reussi a gerer autrement octobre rouge st r1 3 en 3265
				ft_printf(" %s%d", arg_type == REG_CODE ? "r" : "", val);
			else
				ft_printf(" %d", val);

		}
	}
}

void		display_move(t_vm *vm, t_process *proc)
{
	int i;
	int len;

	len = ft_abs(proc->ins_bytelen);

	if (!(vm->display.code & (1 << MSG_MOVE)))
		return ;
	if (proc->pending_ins.op->opcode == ZJMP && proc->carry)
		return ;
	proc->pc = mod(proc->pc, MEM_SIZE);
	ft_printf("\nADV %d (0x%04x -> 0x%04x) ", len, proc->pc, (proc->pc + len));
	i = -1;
	while (++i < len)
		ft_printf("%02x ", (unsigned char)(vm->arena[mod(proc->pc + i, MEM_SIZE)]));
}
